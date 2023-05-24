from a.version cimport *

def version():
    '''algorithm library version'''
    if PY_MAJOR_VERSION >= 3:
        return a_version().decode()
    return a_version()

def version_major() -> int:
    '''algorithm library version major'''
    return a_version_major()

def version_minor() -> int:
    '''algorithm library version minor'''
    return a_version_minor()

def version_patch() -> int:
    '''algorithm library version patch'''
    return a_version_patch()
