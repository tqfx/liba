if not get_option('python')
    subdir_done()
endif

add_languages('cython')

python.extension_module(
    'liba',
    'src/liba.pyx',
    c_args: c_args,
    cpp_args: c_args,
    dependencies: python.dependency(),
    implicit_include_directories: false,
    include_directories: a_include,
    install: true,
    install_dir: python.get_path('platlib'),
    link_with: a.get_static_lib(),
)
