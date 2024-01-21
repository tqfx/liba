from a.crc cimport *

@cython.wraparound(False)
@cython.boundscheck(False)
cdef class crc8:
    cdef array table
    property table:
        def __get__(self):
            return self.table
    def __init__(self, poly: a_u8, reversed = False):
        self.table = array_u8([0] * 0x100)
        if reversed:
            a_crc8l_init(<a_u8 *>self.table.data.as_voidptr, poly)
        else:
            a_crc8m_init(<a_u8 *>self.table.data.as_voidptr, poly)
    def __call__(self, data: bytes, init: a_u8 = 0) -> a_u8:
        return a_crc8(<a_u8 *>self.table.data.as_voidptr, <const void *>data, len(data), init)

@cython.wraparound(False)
@cython.boundscheck(False)
cdef class crc16:
    cdef array table
    property table:
        def __get__(self):
            return self.table
    cdef a_u16 (*call)(const a_u16 *, const void *, a_size, a_u16)
    def __init__(self, poly: a_u16, reversed = False):
        self.table = array_u16([0] * 0x100)
        if reversed:
            self.call = a_crc16l
            a_crc16l_init(<a_u16 *>self.table.data.as_voidptr, poly)
        else:
            self.call = a_crc16m
            a_crc16m_init(<a_u16 *>self.table.data.as_voidptr, poly)
    def __call__(self, data: bytes, init: a_u16 = 0) -> a_u16:
        return self.call(<a_u16 *>self.table.data.as_voidptr, <const void *>data, len(data), init)

@cython.wraparound(False)
@cython.boundscheck(False)
cdef class crc32:
    cdef array table
    property table:
        def __get__(self):
            return self.table
    cdef a_u32 (*call)(const a_u32 *, const void *, a_size, a_u32)
    def __init__(self, poly: a_u32, reversed = False):
        self.table = array_u32([0] * 0x100)
        if reversed:
            self.call = a_crc32l
            a_crc32l_init(<a_u32 *>self.table.data.as_voidptr, poly)
        else:
            self.call = a_crc32m
            a_crc32m_init(<a_u32 *>self.table.data.as_voidptr, poly)
    def __call__(self, data: bytes, init: a_u32 = 0) -> a_u32:
        return self.call(<a_u32 *>self.table.data.as_voidptr, <const void *>data, len(data), init)

@cython.wraparound(False)
@cython.boundscheck(False)
cdef class crc64:
    cdef array table
    property table:
        def __get__(self):
            return self.table
    cdef a_u64 (*call)(const a_u64 *, const void *, a_size, a_u64)
    def __init__(self, poly: a_u64, reversed = False):
        self.table = array_u64([0] * 0x100)
        if reversed:
            self.call = a_crc64l
            a_crc64l_init(<a_u64 *>self.table.data.as_voidptr, poly)
        else:
            self.call = a_crc64m
            a_crc64m_init(<a_u64 *>self.table.data.as_voidptr, poly)
    def __call__(self, data: bytes, init: a_u64 = 0) -> a_u64:
        return self.call(<a_u64 *>self.table.data.as_voidptr, <const void *>data, len(data), init)
