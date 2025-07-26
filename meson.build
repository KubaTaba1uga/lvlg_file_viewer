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
if get_option('buildtype').startswith('debug')
  add_project_arguments(['-fno-inline', '-fno-inline-functions', '-DDEBUG'], language : 'c')
endif

cmake = import('cmake')
opt_var = cmake.subproject_options()
opt_var.add_cmake_defines({'CONFIG_LV_BUILD_EXAMPLES': 'OFF',
                           'CONFIG_LV_BUILD_DEMOS': 'OFF',
			   'LV_CONF_INCLUDE_SIMPLE': true,
			   })

lvgl_proj = cmake.subproject('lvgl', options: opt_var)
lvgl_dep = lvgl_proj.dependency('lvgl')

call_processor_deps = [lvgl_dep]

call_processor_inc = include_directories('src', 'subprojects/lvgl')
# call_processor_inc = include_directories('src')

subdir('src')

executable('call_processor',
  sources: sources,
  include_directories: call_processor_inc,
  dependencies: call_processor_deps,
  c_args: []
)

# ******************************************************************************
# *    Tests
# ******************************************************************************
if get_option('tests')
   subdir('test')
endif
