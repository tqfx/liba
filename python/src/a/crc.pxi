from a.crc cimport *

cdef class crc8:
    cdef readonly array table
    def __cinit__(self):
        self.table = array_u8((0,) * 0x100)
    def gen(self, a_u8 poly, bint reversed = False):
        if reversed:
            a_crc8l_init(<a_u8 *>self.table.data.as_voidptr, poly)
        else:
            a_crc8m_init(<a_u8 *>self.table.data.as_voidptr, poly)
        return self
    def __init__(self, a_u8 poly, bint reversed = False):
        self.gen(poly, reversed)
    def __call__(self, bytes block, a_u8 value = 0):
        cdef const unsigned char *p = <const unsigned char *>block
        return a_crc8(<a_u8 *>self.table.data.as_voidptr, p, len(block), value)
    def pack(self, bytes block, a_u8 value = 0):
        cdef size_t n = len(block)
        block = block + bytes(1)
        cdef unsigned char *p = <unsigned char *>block
        value = a_crc8(<a_u8 *>self.table.data.as_voidptr, p, n, value)
        p[n] = value
        return block

cdef class crc16:
    cdef readonly array table
    def __cinit__(self):
        self.table = array_u16((0,) * 0x100)
    cdef a_u16 (*eval)(const a_u16 *, const void *, a_size, a_u16)
    def gen(self, a_u16 poly, bint reversed = False):
        if reversed:
            a_crc16l_init(<a_u16 *>self.table.data.as_voidptr, poly)
            self.eval = a_crc16l
        else:
            a_crc16m_init(<a_u16 *>self.table.data.as_voidptr, poly)
            self.eval = a_crc16m
        return self
    def __init__(self, a_u16 poly, bint reversed = False):
        self.gen(poly, reversed)
    def __call__(self, bytes block, a_u16 value = 0):
        cdef const unsigned char *p = <const unsigned char *>block
        return self.eval(<a_u16 *>self.table.data.as_voidptr, p, len(block), value)
    def pack(self, bytes block, a_u16 value = 0):
        cdef size_t n = len(block)
        block = block + bytes(2)
        cdef unsigned char *p = <unsigned char *>block
        value = self.eval(<a_u16 *>self.table.data.as_voidptr, p, n, value)
        if self.eval == a_crc16m:
            a_u16_setb(p + n, value)
        else:
            a_u16_setl(p + n, value)
        return block

cdef class crc32:
    cdef readonly array table
    def __cinit__(self):
        self.table = array_u32((0,) * 0x100)
    cdef a_u32 (*eval)(const a_u32 *, const void *, a_size, a_u32)
    def gen(self, a_u32 poly, bint reversed = False):
        if reversed:
            a_crc32l_init(<a_u32 *>self.table.data.as_voidptr, poly)
            self.eval = a_crc32l
        else:
            a_crc32m_init(<a_u32 *>self.table.data.as_voidptr, poly)
            self.eval = a_crc32m
        return self
    def __init__(self, a_u32 poly, bint reversed = False):
        self.gen(poly, reversed)
    def __call__(self, bytes block, a_u32 value = 0):
        cdef const unsigned char *p = <const unsigned char *>block
        return self.eval(<a_u32 *>self.table.data.as_voidptr, p, len(block), value)
    def pack(self, bytes block, a_u32 value = 0):
        cdef size_t n = len(block)
        block = block + bytes(4)
        cdef unsigned char *p = <unsigned char *>block
        value = self.eval(<a_u32 *>self.table.data.as_voidptr, p, n, value)
        if self.eval == a_crc32m:
            a_u32_setb(p + n, value)
        else:
            a_u32_setl(p + n, value)
        return block

cdef class crc64:
    cdef readonly array table
    def __cinit__(self):
        self.table = array_u64((0,) * 0x100)
    cdef a_u64 (*eval)(const a_u64 *, const void *, a_size, a_u64)
    def gen(self, a_u64 poly, bint reversed = False):
        if reversed:
            a_crc64l_init(<a_u64 *>self.table.data.as_voidptr, poly)
            self.eval = a_crc64l
        else:
            a_crc64m_init(<a_u64 *>self.table.data.as_voidptr, poly)
            self.eval = a_crc64m
        return self
    def __init__(self, a_u64 poly, bint reversed = False):
        self.gen(poly, reversed)
    def __call__(self, bytes block, a_u64 value = 0):
        cdef const unsigned char *p = <const unsigned char *>block
        return self.eval(<a_u64 *>self.table.data.as_voidptr, p, len(block), value)
    def pack(self, bytes block, a_u64 value = 0):
        cdef size_t n = len(block)
        block = block + bytes(8)
        cdef unsigned char *p = <unsigned char *>block
        value = self.eval(<a_u64 *>self.table.data.as_voidptr, p, n, value)
        if self.eval == a_crc64m:
            a_u64_setb(p + n, value)
        else:
            a_u64_setl(p + n, value)
        return block
