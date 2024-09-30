project('liba', 'c', 'cpp',
        default_options: [
            'c_std=c11',
            'cpp_std=c++11',
            'b_ndebug=if-release',
            'buildtype=debugoptimized',
        ],
        license: 'MPL-2.0',
        version: '0.1.15')

a_have_h = configuration_data()
a_have_h.set('version', meson.version())
a_have_h.set('A_VERSION', meson.project_version())
a_have_h.set('A_VERSION_MAJOR', meson.project_version().split('.')[0])
a_have_h.set('A_VERSION_MINOR', meson.project_version().split('.')[1])
a_have_h.set('A_VERSION_PATCH', meson.project_version().split('.')[2])
a_have_h.set('A_SIZE_FLOAT', get_option('float'))
if target_machine.endian() == 'little'
    a_have_h.set('A_BYTE_ORDER', 1234)
elif target_machine.endian() == 'big'
    a_have_h.set('A_BYTE_ORDER', 4321)
endif

compiler = meson.get_compiler('c')
a_have_h.set('A_SIZE_POINTER', compiler.sizeof('void *'))

math = ['expm1', 'log1p', 'hypot', 'atan2',
        'csqrt', 'cpow', 'cexp', 'clog',
        'csin', 'ccos', 'ctan',
        'csinh', 'ccosh', 'ctanh',
        'casin', 'cacos', 'catan',
        'casinh', 'cacosh', 'catanh']

foreach func: math
    float = get_option('float').to_int()
    have = 'A_HAVE_' + func.to_upper()
    if  float == 4
        func = func + 'f'
    elif float > 8
        func = func + 'l'
    endif
    if compiler.has_function(func)
        a_have_h.set(have, '1')
    endif
endforeach

configure_file(
    input: 'include/a.meson.h.in',
    output: 'a.meson.h',
    configuration: a_have_h,
)

c_args = []
sources = [
    'include/a/a.h',
    'include/a/avl.h',
    'include/a/buf.h',
    'include/a/complex.h',
    'include/a/crc.h',
    'include/a/fuzzy.h',
    'include/a/hpf.h',
    'include/a/list.h',
    'include/a/lpf.h',
    'include/a/math.h',
    'include/a/mf.h',
    'include/a/notefreqs.h',
    'include/a/pid.h',
    'include/a/pid_fuzzy.h',
    'include/a/pid_neuro.h',
    'include/a/poly.h',
    'include/a/que.h',
    'include/a/rbt.h',
    'include/a/regress.h',
    'include/a/regress_linear.h',
    'include/a/regress_simple.h',
    'include/a/slist.h',
    'include/a/str.h',
    'include/a/tf.h',
    'include/a/trajbell.h',
    'include/a/trajpoly3.h',
    'include/a/trajpoly5.h',
    'include/a/trajpoly7.h',
    'include/a/trajtrap.h',
    'include/a/utf.h',
    'include/a/vec.h',
    'include/a/version.h',
    'src/a.c',
    'src/avl.c',
    'src/buf.c',
    'src/complex.c',
    'src/crc.c',
    'src/fuzzy.c',
    'src/math.c',
    'src/mf.c',
    'src/pid.c',
    'src/pid_fuzzy.c',
    'src/pid_neuro.c',
    'src/poly.c',
    'src/que.c',
    'src/rbt.c',
    'src/regress.c',
    'src/regress_linear.c',
    'src/regress_simple.c',
    'src/str.c',
    'src/tf.c',
    'src/trajbell.c',
    'src/trajpoly3.c',
    'src/trajpoly5.c',
    'src/trajpoly7.c',
    'src/trajtrap.c',
    'src/utf.c',
    'src/vec.c',
    'src/version.c',
]

a_include = include_directories('include')
a_meson_h = meson.current_build_dir() / 'a.meson.h'
a_h = meson.current_source_dir() / 'include' / 'a' / 'a.h'

python = import('python').find_installation()
res = run_command(python, '-c', '''import os, sys
dir = os.path.dirname('@1@')
src = os.path.basename('@0@')
dst = os.path.basename('@1@')
cur = "#if defined(A_HAVE_H)"
new = '#include "' + dst + '"\n' + cur
with open('@0@', "r") as f:
    txt = f.read()
res = txt.replace(cur, new)
if res != txt:
    new = os.path.join(dir, src)
    with open(new, "wb") as f:
        f.write(res.encode())
dir = os.path.dirname('@0@')
res = os.path.relpath('@1@', dir)
sys.stdout.write(res.replace("\\", "/"))
'''.format(a_h, a_meson_h), capture: true, check: true
)
if res.returncode() == 0
    c_args += ['-DA_EXPORTS', '-DA_HAVE_H="' + res.stdout() + '"']
endif

a = both_libraries('a', sources, c_args: c_args, cpp_args: c_args,
    dependencies: compiler.find_library('m', required: false),
    implicit_include_directories: false,
    include_directories: a_include,
    install: true,
    link_args: get_option('math'),
    name_prefix: 'lib',
    pic: true,
    version: meson.project_version(),
)

install_headers(a_meson_h, subdir: 'a')
install_headers(meson.current_build_dir() / 'a.h', subdir: 'a')
install_subdir('include/a', exclude_files: ['a.h'],
    install_dir: get_option('includedir'),
)

if get_option('rust')
    rust_args = []
    add_languages('rust')
    if get_option('float').to_int() == 4
        rust_args += ['--cfg', 'feature="float"']
    endif
    static_library('liba', 'src/lib.rs',
        rust_args: rust_args,
        install: true,
        link_with: a.get_static_lib(),
    )
endif

subdir('java')
subdir('lua')
subdir('python')
subdir('quickjs')
