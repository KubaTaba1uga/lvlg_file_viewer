######################################################################################
#                               Imports                                              #
######################################################################################
import glob
import os
import shutil
import subprocess

from invoke import UnexpectedExit, task

######################################################################################
#                       Tool Configuration Variables                                 #
######################################################################################
C_COMPILER = "clang-19"
C_FORMATTER = "clang-format-19"
C_LINTTER = "clang-tidy-19"
C_LINKER = "lld-19"
DOCKER_IMAGE_TAG = "call-registry-call-processor"

######################################################################################
#                             Public API                                             #
######################################################################################
ROOT_PATH = os.path.dirname(os.path.abspath(__file__))
SRC_PATH = os.path.join(ROOT_PATH, "src")
BUILD_PATH = os.path.join(ROOT_PATH, "build")
TEST_PATH = os.path.join(ROOT_PATH, "test")


@task
def install(c):
    """
    Install dependencies if they are not already installed.

    Usage:
        inv install
    """
    dependencies = {
        "git": "git",
        "ruby": "ruby",
        "meson": "meson",
        "cmake": "cmake",
        C_COMPILER: C_COMPILER,
        C_FORMATTER: C_FORMATTER,
        C_LINTTER: C_LINTTER,
        C_LINKER: C_LINKER,
    }

    _pr_info("Installing dependencies...")

    for dep_cmd, dep_package in dependencies.items():
        if not _command_exists(dep_cmd):
            _pr_warn(f"{dep_cmd} not found. Installing {dep_package}...")
            _run_command(c, f"apt-get install -y {dep_package}")
        else:
            _pr_info(f"{dep_package} already installed")

    _run_command(c, "apt-get build-dep -y libcurl4=7.88.1-10+deb12u12")

    _pr_info("Dependencies installed")


@task
def build(c, backtrace=False, debug=False, tests=False, examples=False):
    """
    Configure and build the project.

    Args:
        backtrace (bool): Enable backtrace support. Usage: inv build --backtrace
        debug (bool): Build with debug symbols. Usage: inv build --debug
    """
    _pr_info("Building...")

    _run_command(c, f"mkdir -p {BUILD_PATH}")

    setup_command = f"CC={C_COMPILER} meson setup {BUILD_PATH}"

    if backtrace:
        setup_command = f"{setup_command} -Dbacktrace=true"

    if debug:
        setup_command = f"{setup_command} -Db_sanitize=address,undefined -Db_lundef=false -Dbuildtype=debug"
    else:
        setup_command = f"{setup_command} -Dbuildtype=release"

    if tests:
        setup_command = f"{setup_command} -Dtests=true"

    _run_command(c, setup_command)
    _run_command(c, f"meson compile -v -C {BUILD_PATH}")

    _pr_info("Build done")


@task(iterable=["name"])
def test(c, name=None):
    _pr_info("Testing...")

    # Base test command
    cmd = f"meson test -C {BUILD_PATH} --verbose"

    # Add test name(s) if provided
    if name:
        name_args = " ".join(name)
        cmd += f" {name_args}"

    _run_command(c, cmd)

    _pr_info("Testing done")


@task
def lint(c):
    patterns = [
        "src/**/*.c",
        "src/**/*.h",
        "include/**/*.h",
    ]
    _pr_info("Linting...")

    cmd = f"{C_LINTTER} --extra-arg=-v -p {BUILD_PATH}"

    for pattern in patterns:
        _pr_info(f"Linting files matching pattern '{pattern}'")

        for path in glob.glob(pattern, recursive=True):
            if os.path.isfile(path):
                _run_command(c, f"{cmd} {path}")
                _pr_info(f"{path} linted")

    _pr_info("Linting done")


@task
def format(c, diff_only=False):
    patterns = [
        "src/**/*.c",
        "src/**/*.h",
        "include/**/*.h",
        "test/**/*.c",
        "test/**/*.h",
    ]
    blacklist = ["yyjson.c", "yyjson.h"]
    _pr_info("Formating...")

    cmd = f"{C_FORMATTER}"

    if diff_only:
        cmd += " --dry-run --Werror "

    for pattern in patterns:
        _pr_info(f"Formating files matching pattern '{pattern}'")

        for path in glob.glob(pattern, recursive=True):
            if any([black in path for black in blacklist]):
                continue

            if os.path.isfile(path):
                _run_command(c, f"{cmd} -i {path}")
                _pr_info(f"{path} formated")

    _pr_info("Formating done")


@task
def clean(c, extra=""):
    """
    Clean up build and temporary files recursively.

    This task removes specified patterns of files and directories,
    including build artifacts and temporary files.

    Args:
        extra (str, optional): Additional pattern to remove. Defaults to "".

    Usage:
        inv clean
        inv clean --bytecode
        inv clean --extra='**/*.log'
    """
    patterns = [
        "build",
        ".cache",
        "**/*~",
        "*~",
        "**/*#*",
        "*#*",
        "**/.#*",
        ".#*",
    ]

    if extra:
        patterns.append(extra)

    for pattern in patterns:
        _pr_info(f"Removing files matching pattern '{pattern}'")

        for path in glob.glob(pattern, recursive=True):
            if os.path.isdir(path):
                shutil.rmtree(path)
                _pr_debug(f"Removed directory {path}")
            else:
                os.remove(path)
                _pr_debug(f"Removed file {path}")

    _pr_info("Clean up completed.")


@task
def build_docker_image(c, repo_path=ROOT_PATH):
    _pr_info("Building Docker image…")
    _check_docker(c)

    _run_command(
        c,
        """
eval "$(ssh-agent -s)"
ssh-add
DOCKER_BUILDKIT=1 docker build \
  --ssh default \
  --build-arg GIT_METHOD=ssh \
  -t {tag} \
  -f docker/Dockerfile .
        """.format(tag=DOCKER_IMAGE_TAG),
    )

    _pr_info("Docker image build completed.")


######################################################################################
#                                  Private API                                       #
######################################################################################
def _get_file_extension(file_path):
    _, file_extension = os.path.splitext(file_path)
    return file_extension


def _command_exists(command):
    try:
        subprocess.run(
            [command, "--version"], stdout=subprocess.PIPE, stderr=subprocess.PIPE
        )
        return True
    except FileNotFoundError:
        return False
    except subprocess.CalledProcessError:
        return True
    except Exception:
        return False


def _run_command(c, command):
    _pr_debug(f"Executing '{command}'...")

    try:
        result = c.run(command, warn=True)

        if not result.ok:
            raise Exception("Result not ok")

    except Exception as exc:
        _pr_error(f"Command {command} failed: {exc}")
        exit(1)


def _check_docker(c):
    """Verify Docker CLI availability."""
    try:
        result = c.run("docker --version", hide=True, warn=True)
        if result.ok:
            _pr_info(f"Docker detected: {result.stdout.strip()}")
    except UnexpectedExit:
        _pr_error("Docker command unavailable.")
        raise RuntimeError("Docker is not installed or not in PATH.")


def _cut_path_to_directory(full_path, target_directory):
    parts = full_path.split(os.sep)
    target_index = parts.index(target_directory)
    return os.sep.join(parts[: target_index + 1])


def _pr_info(message: str):
    print(f"\033[94m[INFO] {message}\033[0m")


def _pr_warn(message: str):
    print(f"\033[93m[WARN] {message}\033[0m")


def _pr_debug(message: str):
    print(f"\033[96m[DEBUG] {message}\033[0m")


def _pr_error(message: str):
    print(f"\033[91m[ERROR] {message}\033[0m")
