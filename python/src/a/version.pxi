from a.version cimport *

VERSION = A_VERSION.decode()
def version():
    '''algorithm library version'''
    if PY_MAJOR_VERSION >= 3:
        return a_version().decode()
    return a_version()

VERSION_MAJOR = A_VERSION_MAJOR
def version_major() -> int:
    '''algorithm library version major'''
    return a_version_major()

VERSION_MINOR = A_VERSION_MINOR
def version_minor() -> int:
    '''algorithm library version minor'''
    return a_version_minor()

VERSION_PATCH = A_VERSION_PATCH
def version_patch() -> int:
    '''algorithm library version patch'''
    return a_version_patch()
