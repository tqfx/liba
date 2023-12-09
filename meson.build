project('liba', 'c', 'cpp',
        default_options: [
            'c_std=c11',
            'cpp_std=c++11',
            'b_ndebug=if-release',
            'default_library=both',
            'buildtype=debugoptimized',
        ],
        license: 'MPL-2.0',
        version: '0.1.1')

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

math = ['hypot', 'log1p', 'atan2',
        'csqrt', 'cpow', 'cexp', 'clog',
        'csin', 'ccos', 'ctan',
        'csinh', 'ccosh', 'ctanh',
        'casin', 'cacos', 'catan',
        'casinh', 'cacosh', 'catanh']

foreach func: math
    float = get_option('float').to_int()
    have = 'A_HAVE_@0@'.format(func.to_upper())
    if  float == 4
        func = func + 'f'
    elif float > 8
        func = func + 'l'
    endif
    if compiler.has_function(func)
        a_have_h.set(have, '1')
    endif
endforeach

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
    'include/a/operator.h',
    'include/a/pid.h',
    'include/a/pid_fuzzy.h',
    'include/a/pid_neuron.h',
    'include/a/poly.h',
    'include/a/polytraj.h',
    'include/a/que.h',
    'include/a/rbf.h',
    'include/a/rbt.h',
    'include/a/slist.h',
    'include/a/str.h',
    'include/a/tf.h',
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
    'src/pid_neuron.c',
    'src/poly.c',
    'src/polytraj.c',
    'src/que.c',
    'src/rbf.c',
    'src/rbt.c',
    'src/str.c',
    'src/tf.c',
    'src/utf.c',
    'src/vec.c',
    'src/version.c',
    'src/version.cpp',
]

python = import('python').find_installation()
fixup_py = join_paths(meson.current_source_dir(), 'meson', 'fixup.py')
a_meson_h = join_paths(meson.current_build_dir(), 'a.meson.h')
a_h = configure_file(output: 'a.h', input: 'include/a/a.h',
    command: [python, fixup_py, a_meson_h, '@INPUT@']
)

configure_file(input: 'include/a.meson.h.in', output: 'a.meson.h', configuration: a_have_h)
add_project_arguments('-DA_EXPORTS', '-DA_HAVE_H="a.meson.h"', language: ['c', 'cpp'])
library('a', sources,
        dependencies: compiler.find_library('m', required: false),
        include_directories: include_directories('include'),
        soversion: meson.project_version().split('.')[0],
        version: meson.project_version(),
        link_args: get_option('math'),
        install: true)

install_headers(a_h, subdir: 'a')
install_headers(a_meson_h, subdir: 'a')
install_subdir('include/a', install_dir: get_option('includedir'))
