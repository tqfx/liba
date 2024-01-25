from a.crc cimport *

@cython.wraparound(False)
@cython.boundscheck(False)
cdef class crc8:
    cdef array table
    property table:
        def __get__(self):
            return self.table
    def gen(self, poly: a_u8, reversed = False):
        if reversed:
            a_crc8l_init(<a_u8 *>self.table.data.as_voidptr, poly)
        else:
            a_crc8m_init(<a_u8 *>self.table.data.as_voidptr, poly)
        return self
    def __init__(self, poly: a_u8, reversed = False):
        self.table = array_u8([0] * 0x100)
        self.gen(poly, reversed)
    def __call__(self, block: bytes, value: a_u8 = 0) -> a_u8:
        cdef const unsigned char *p = <const unsigned char *>block
        return a_crc8(<a_u8 *>self.table.data.as_voidptr, p, len(block), value)
    def pack(self, block: bytes, value: a_u8 = 0) -> bytes:
        cdef size_t n = len(block)
        block = block + bytes(1)
        cdef unsigned char *p = <unsigned char *>block
        value = a_crc8(<a_u8 *>self.table.data.as_voidptr, p, n, value)
        p[n] = value
        return block

@cython.wraparound(False)
@cython.boundscheck(False)
cdef class crc16:
    cdef array table
    property table:
        def __get__(self):
            return self.table
    cdef a_u16 (*eval)(const a_u16 *, const void *, a_size, a_u16)
    def gen(self, poly: a_u16, reversed = False):
        if reversed:
            a_crc16l_init(<a_u16 *>self.table.data.as_voidptr, poly)
            self.eval = a_crc16l
        else:
            a_crc16m_init(<a_u16 *>self.table.data.as_voidptr, poly)
            self.eval = a_crc16m
        return self
    def __init__(self, poly: a_u16, reversed = False):
        self.table = array_u16([0] * 0x100)
        self.gen(poly, reversed)
    def __call__(self, block: bytes, value: a_u16 = 0) -> a_u16:
        cdef const unsigned char *p = <const unsigned char *>block
        return self.eval(<a_u16 *>self.table.data.as_voidptr, p, len(block), value)
    def pack(self, block: bytes, value: a_u16 = 0) -> bytes:
        cdef size_t n = len(block)
        block = block + bytes(2)
        cdef unsigned char *p = <unsigned char *>block
        value = self.eval(<a_u16 *>self.table.data.as_voidptr, p, n, value)
        if self.eval == a_crc16m:
            a_u16_setb(p + n, value)
        else:
            a_u16_setl(p + n, value)
        return block

@cython.wraparound(False)
@cython.boundscheck(False)
cdef class crc32:
    cdef array table
    property table:
        def __get__(self):
            return self.table
    cdef a_u32 (*eval)(const a_u32 *, const void *, a_size, a_u32)
    def gen(self, poly: a_u32, reversed = False):
        if reversed:
            a_crc32l_init(<a_u32 *>self.table.data.as_voidptr, poly)
            self.eval = a_crc32l
        else:
            a_crc32m_init(<a_u32 *>self.table.data.as_voidptr, poly)
            self.eval = a_crc32m
        return self
    def __init__(self, poly: a_u32, reversed = False):
        self.table = array_u32([0] * 0x100)
        self.gen(poly, reversed)
    def __call__(self, block: bytes, value: a_u32 = 0) -> a_u32:
        cdef const unsigned char *p = <const unsigned char *>block
        return self.eval(<a_u32 *>self.table.data.as_voidptr, p, len(block), value)
    def pack(self, block: bytes, value: a_u32 = 0) -> bytes:
        cdef size_t n = len(block)
        block = block + bytes(4)
        cdef unsigned char *p = <unsigned char *>block
        value = self.eval(<a_u32 *>self.table.data.as_voidptr, p, n, value)
        if self.eval == a_crc32m:
            a_u32_setb(p + n, value)
        else:
            a_u32_setl(p + n, value)
        return block

@cython.wraparound(False)
@cython.boundscheck(False)
cdef class crc64:
    cdef array table
    property table:
        def __get__(self):
            return self.table
    cdef a_u64 (*eval)(const a_u64 *, const void *, a_size, a_u64)
    def gen(self, poly: a_u64, reversed = False):
        if reversed:
            a_crc64l_init(<a_u64 *>self.table.data.as_voidptr, poly)
            self.eval = a_crc64l
        else:
            a_crc64m_init(<a_u64 *>self.table.data.as_voidptr, poly)
            self.eval = a_crc64m
        return self
    def __init__(self, poly: a_u64, reversed = False):
        self.table = array_u64([0] * 0x100)
        self.gen(poly, reversed)
    def __call__(self, block: bytes, value: a_u64 = 0) -> a_u64:
        cdef const unsigned char *p = <const unsigned char *>block
        return self.eval(<a_u64 *>self.table.data.as_voidptr, p, len(block), value)
    def pack(self, block: bytes, value: a_u64 = 0) -> bytes:
        cdef size_t n = len(block)
        block = block + bytes(8)
        cdef unsigned char *p = <unsigned char *>block
        value = self.eval(<a_u64 *>self.table.data.as_voidptr, p, n, value)
        if self.eval == a_crc64m:
            a_u64_setb(p + n, value)
        else:
            a_u64_setl(p + n, value)
        return block
