from a.version cimport *

'''algorithm library version'''
if PY_MAJOR_VERSION >= 3:
    VERSION = A_VERSION.decode()
else:
    VERSION = A_VERSION

@cython.wraparound(False)
@cython.boundscheck(False)
cdef class version:
    '''version'''
    cdef a_version ctx
    property major:
        def __get__(self):
            return self.ctx.major
        def __set__(self, major):
            self.ctx.major = major
    property minor:
        def __get__(self):
            return self.ctx.minor
        def __set__(self, minor):
            self.ctx.minor = minor
    property third:
        def __get__(self):
            return self.ctx.third
        def __set__(self, third):
            self.ctx.third = third
    property extra:
        def __get__(self):
            return self.ctx.extra
        def __set__(self, extra):
            self.ctx.extra = extra
    def __init__(self, major = 0, minor = 0, third = 0, extra = 0):
        self.ctx.major = major
        self.ctx.minor = minor
        self.ctx.third = third
        self.ctx.extra = extra
    def __repr__(self):
        if self.ctx.extra == 0:
            return "%u.%u.%u" % (self.ctx.major, self.ctx.minor, self.ctx.third)
        return "%u.%u.%u.%u" % (self.ctx.major, self.ctx.minor, self.ctx.third, self.ctx.extra)
    def compare(self, other: version):
        return a_version_cmp(&self.ctx, &other.ctx)
    def __lt__(self, other: version):
        return a_version_lt(&self.ctx, &other.ctx)
    def __gt__(self, other: version):
        return a_version_gt(&self.ctx, &other.ctx)
    def __le__(self, other: version):
        return a_version_le(&self.ctx, &other.ctx)
    def __ge__(self, other: version):
        return a_version_ge(&self.ctx, &other.ctx)
    def __eq__(self, other: version):
        return a_version_eq(&self.ctx, &other.ctx)
    def __ne__(self, other: version):
        return a_version_ne(&self.ctx, &other.ctx)
    def parse(self, ver: bytes):
        a_version_parse(&self.ctx, ver)
        return self
    @staticmethod
    def check(unsigned int major = 0, unsigned int minor = 0, unsigned int patch = 0):
        return a_version_check(major, minor, patch)
    '''algorithm library version major'''
    MAJOR = A_VERSION_MAJOR
    '''algorithm library version minor'''
    MINOR = A_VERSION_MINOR
    '''algorithm library version patch'''
    PATCH = A_VERSION_PATCH
    '''algorithm library version tweak'''
    TWEAK = A_VERSION_TWEAK
