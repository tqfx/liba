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
    'src/tf.c',
    'src/trajbell.c',
    'src/trajpoly3.c',
    'src/trajpoly5.c',
    'src/trajpoly7.c',
    'src/trajtrap.c',
    'src/version.c',
]

dep = compiler.find_library('quickjs', dirs: get_option('quickjs') / 'lib/quickjs')
if build_machine.system() != 'windows'
    dep = []
endif

include = include_directories(get_option('quickjs') / 'include/quickjs')

shared_module(
    'a', sources,
    c_args: a_args,
    cpp_args: a_args,
    dependencies: dep,
    implicit_include_directories: false,
    include_directories: [a_include, include],
    install: true,
    install_dir: get_option('libdir') / 'quickjs',
    link_with: a.get_static_lib(),
    name_prefix: 'lib',
    name_suffix: 'so',
)
