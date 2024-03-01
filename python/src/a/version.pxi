from a.version cimport *

if PY_MAJOR_VERSION >= 3:
    VERSION = A_VERSION.decode()
else:
    VERSION = A_VERSION

cdef class version:
    cdef a_version ctx
    def __init__(self, unsigned int major = 0, unsigned int minor = 0, unsigned int third = 0, unsigned int extra = 0):
        self.ctx.major = major
        self.ctx.minor = minor
        self.ctx.third = third
        self.ctx.extra = extra
        self.ctx.alpha[0] = 46
    def __repr__(self):
        cdef char str[48]
        a_version_tostr(&self.ctx, str, sizeof(str))
        return str.decode()
    @staticmethod
    def check(unsigned int major = 0, unsigned int minor = 0, unsigned int patch = 0):
        return a_version_check(major, minor, patch)
    def cmp(self, version that):
        return a_version_cmp(&self.ctx, &that.ctx)
    def __lt__(self, version that):
        return a_version_lt(&self.ctx, &that.ctx)
    def __gt__(self, version that):
        return a_version_gt(&self.ctx, &that.ctx)
    def __le__(self, version that):
        return a_version_le(&self.ctx, &that.ctx)
    def __ge__(self, version that):
        return a_version_ge(&self.ctx, &that.ctx)
    def __eq__(self, version that):
        return a_version_eq(&self.ctx, &that.ctx)
    def __ne__(self, version that):
        return a_version_ne(&self.ctx, &that.ctx)
    def parse(self, bytes ver):
        a_version_parse(&self.ctx, ver)
        return self
    property major:
        def __get__(self):
            return self.ctx.major
        def __set__(self, unsigned int major):
            self.ctx.major = major
    property minor:
        def __get__(self):
            return self.ctx.minor
        def __set__(self, unsigned int minor):
            self.ctx.minor = minor
    property third:
        def __get__(self):
            return self.ctx.third
        def __set__(self, unsigned int third):
            self.ctx.third = third
    property extra:
        def __get__(self):
            return self.ctx.extra
        def __set__(self, unsigned int extra):
            self.ctx.extra = extra
    property alpha:
        def __get__(self):
            cdef char alpha[5]
            a_version_alpha(&self.ctx, alpha)
            return alpha
        def __set__(self, bytes alpha):
            a_version_set_alpha(&self.ctx, alpha)
    MAJOR = A_VERSION_MAJOR
    MINOR = A_VERSION_MINOR
    PATCH = A_VERSION_PATCH
    TWEAK = A_VERSION_TWEAK
