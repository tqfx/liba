if get_option('java') == ''
    subdir_done()
endif

sources = [
    'include/liba.h',
    'include/liba_crc16.h',
    'include/liba_crc32.h',
    'include/liba_crc64.h',
    'include/liba_crc8.h',
    'include/liba_hpf.h',
    'include/liba_lpf.h',
    'include/liba_mf.h',
    'include/liba_pid_fuzzy.h',
    'include/liba_pid.h',
    'include/liba_pid_neuro.h',
    'include/liba_tf.h',
    'include/liba_trajbell.h',
    'include/liba_trajpoly3.h',
    'include/liba_trajpoly5.h',
    'include/liba_trajpoly7.h',
    'include/liba_trajtrap.h',
    'include/liba_version.h',
    'src/a.c',
    'src/a.h',
    'src/crc16.c',
    'src/crc32.c',
    'src/crc64.c',
    'src/crc8.c',
    'src/hpf.c',
    'src/lpf.c',
    'src/mf.c',
    'src/pid.c',
    'src/pid_fuzzy.c',
    'src/pid_neuro.c',
    'src/tf.c',
    'src/trajbell.c',
    'src/trajpoly3.c',
    'src/trajpoly5.c',
    'src/trajpoly7.c',
    'src/trajtrap.c',
    'src/version.c',
]

res = run_command(python, '-c', '''import os, sys, glob
res = os.path.join('@0@', 'include', '*', 'jni_md.h')
sys.stdout.write(os.path.dirname(glob.glob(res)[0]))
'''.format(get_option('java')), capture: true, check: true
)
if res.returncode() == 0
    includedir = get_option('java') / 'include'
    include = [
        a_include,
        include_directories('include'),
        include_directories(includedir),
        include_directories(res.stdout()),
    ]
else
    subdir_done()
endif

shared_module(
    'a', sources,
    c_args: a_args,
    cpp_args: a_args,
    implicit_include_directories: false,
    include_directories: include,
    install: true,
    install_dir: get_option('libdir') / 'jni',
    link_with: a.get_static_lib(),
)
