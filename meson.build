project(
  'schedule',
  'cpp',
  version : '0.1',
  meson_version : '>= 1.3.0',
  default_options : ['warning_level=3', 'cpp_std=c++20'],
)

dependencies = [
]

sources = [
  'schedule.cpp',
]

exe = executable(
  'schedule',
  sources,
  install : true,
  dependencies : dependencies,
)

test('basic', exe)

template_schedule_dep = declare_dependency(
    include_directories: include_directories('.'),
)
meson.override_dependency('template_schedule', template_schedule_dep)
