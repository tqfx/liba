if get_option('quickjs') == ''
    subdir_done()
endif

sources = [
    'src/a.c',
    'src/a.h',
    'src/crc16.c',
    'src/crc32.c',
    'src/crc64.c',
    'src/crc8.c',
    'src/hpf.c',
    'src/lpf.c',
    'src/mf.c',
    'src/mf.h',
    'src/pid.c',
    'src/pid_fuzzy.c',
    'src/pid_neuro.c',
    'src/quickjs.c',
    'src/regress_linear.c',
    'src/regress_simple.c',
    'src/tf.c',
    'src/trajbell.c',
    'src/trajpoly3.c',
    'src/trajpoly5.c',
    'src/trajpoly7.c',
    'src/trajtrap.c',
    'src/version.c',
]

includedir = get_option('quickjs') / 'include' / 'quickjs'
include = [a_include, include_directories(includedir)]
libdir = get_option('quickjs') / 'lib' / 'quickjs'

dep = []
if build_machine.system() == 'windows'
    dep += [compiler.find_library('quickjs', dirs: libdir)]
endif

shared_module(
    'a', sources,
    c_args: c_args,
    cpp_args: c_args,
    dependencies: dep,
    implicit_include_directories: false,
    include_directories: include,
    install: true,
    install_dir: get_option('libdir') / 'quickjs',
    link_with: a.get_static_lib(),
    name_prefix: 'lib',
    name_suffix: 'so',
)
