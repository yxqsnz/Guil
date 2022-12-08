project('Guil', 'cpp',
  version : '0.1',
  default_options : ['warning_level=3',
                     'cpp_std=c++14'])
sources = [ 'sources/File.cpp', 'sources/App.cpp' ]

guil = static_library('guil', sources,
  include_directories : [ 'include' ])

E_Files = executable('Files', 'examples/Files.cpp',
  include_directories : [ 'include' ],
  link_with : guil,
  install : true)

test('basic', E_Files)
