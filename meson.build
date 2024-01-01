project('ImGuiWidgets', 'cpp',
  version : '0.1',
  default_options : ['warning_level=3', 'cpp_std=c++20'])

# These arguments are only used to build the shared library
# not the executables that use the library.
lib_args = ['-DBUILDING_IMGUIWIDGETS']

deps = [
  dependency('imguiwrapper'),
  dependency('ren_utils'),
]

src = files(
  './src/FpsPlot.cpp',
  './src/GuiLogger.cpp'
)

stlib = static_library('imguiwidgets', src,
  install : true,
  cpp_args : lib_args,
  gnu_symbol_visibility : 'hidden',
  dependencies : deps,
)

# Make this library usable as a Meson subproject.
imguiwidgets_dep = declare_dependency(
  include_directories: include_directories('src'),
  link_with : stlib)

