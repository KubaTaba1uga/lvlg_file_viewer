# Call Processor
# ******************************************************************************
# *    Project
# ******************************************************************************
project('lvgl_file_viewer', 'c',
         version: '0.0.1',
         meson_version: '>=1.0.1',
         default_options: [
            'werror=true',
            'c_std=c11',
         ],
)

# ******************************************************************************
# *    App
# ******************************************************************************
## Add LVGL
cmake = import('cmake')
opt_var = cmake.subproject_options()
opt_var.add_cmake_defines({'CONFIG_LV_BUILD_EXAMPLES': 'OFF',
                           'CONFIG_LV_BUILD_DEMOS': 'OFF',
			   'LV_CONF_INCLUDE_SIMPLE': true,
			   })
opt_var.append_compile_args('c', '-D_GNU_SOURCE')
lvgl_proj = cmake.subproject('lvgl', options: opt_var)
lvgl_dep = lvgl_proj.dependency('lvgl')

## Add X11
x11_dep  = dependency('x11', required: true)

## Add errors lib
c_minilib_error_dep = dependency('c_minilib_error',
  fallback: ['c_minilib_error', 'c_minilib_error_dep'],
  required: true,
)

## Add STC
stc_dep = dependency('stc',
  fallback: ['stc', 'stc_dep'],
  default_options: ['checkscoped=disabled'],
  required: true,
)

## Add app
lvgl_file_viewer_deps = [lvgl_dep, x11_dep, c_minilib_error_dep, stc_dep]
lvgl_file_viewer_inc = include_directories('src')
add_project_arguments('-D_GNU_SOURCE', language: 'c')
if get_option('buildtype').startswith('debug')
  add_project_arguments(['-fno-inline', '-fno-inline-functions', '-DDEBUG'], language : 'c')
endif

subdir('src')

executable('lvgl_file_viewer',
  sources: sources,
  include_directories: lvgl_file_viewer_inc,
  dependencies: lvgl_file_viewer_deps,
  c_args: []
)

# ******************************************************************************
# *    Tests
# ******************************************************************************
if get_option('tests')
   subdir('test')
endif
