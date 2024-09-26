if get_option('lua') == ''
    subdir_done()
endif

sources = [
    'src/a.c',
    'src/a.h',
    'src/complex.c',
    'src/complex.h',
    'src/crc16.c',
    'src/crc16.h',
    'src/crc32.c',
    'src/crc32.h',
    'src/crc64.c',
    'src/crc64.h',
    'src/crc8.c',
    'src/crc8.h',
    'src/hpf.c',
    'src/hpf.h',
    'src/lpf.c',
    'src/lpf.h',
    'src/lua.c',
    'src/mf.c',
    'src/pid.c',
    'src/pid.h',
    'src/pid_fuzzy.c',
    'src/pid_fuzzy.h',
    'src/pid_neuro.c',
    'src/pid_neuro.h',
    'src/regress_simple.c',
    'src/regress_simple.h',
    'src/tf.c',
    'src/tf.h',
    'src/trajbell.c',
    'src/trajbell.h',
    'src/trajpoly3.c',
    'src/trajpoly3.h',
    'src/trajpoly5.c',
    'src/trajpoly5.h',
    'src/trajpoly7.c',
    'src/trajpoly7.h',
    'src/trajtrap.c',
    'src/trajtrap.h',
    'src/version.c',
    'src/version.h',
]

lua = dependency(get_option('lua'))
if lua.version().version_compare('>5')
    s = lua.version().split('.')
    ver = s[0] + '.' + s[1]
else
    ver = '5.1'
endif

shared_module(
    'a', sources,
    c_args: c_args,
    cpp_args: c_args,
    dependencies: lua,
    implicit_include_directories: false,
    include_directories: a_include,
    install: true,
    install_dir: get_option('libdir') / 'lua' / ver,
    link_with: a.get_static_lib(),
    name_prefix: 'lib',
)
