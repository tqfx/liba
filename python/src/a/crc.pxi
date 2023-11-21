from a.crc cimport *

@cython.wraparound(False)
@cython.boundscheck(False)
cdef class crc8:
    POLY = A_CRC8_POLY
    INIT = A_CRC8_INIT
    cdef array table
    property table:
        def __get__(self):
            return self.table
    def __init__(self, poly: a_u8_t = A_CRC8_POLY, be = False):
        self.table = u8.array([0] * A_CRC_SIZ)
        if be:
            a_crc8be_init(<a_u8_t *>self.table.data.as_voidptr, poly)
        else:
            a_crc8le_init(<a_u8_t *>self.table.data.as_voidptr, poly)
    def __call__(self, data: bytes, init: a_u8_t = A_CRC8_INIT) -> a_u8_t:
        return a_crc8(<a_u8_t *>self.table.data.as_voidptr, <const void *>data, len(data), init)

@cython.wraparound(False)
@cython.boundscheck(False)
cdef class crc16:
    POLY = A_CRC16_POLY
    INIT = A_CRC16_INIT
    cdef array table
    property table:
        def __get__(self):
            return self.table
    cdef a_u16_t (*call)(const a_u16_t *, const void *, a_size_t, a_u16_t)
    def __init__(self, poly: a_u16_t = A_CRC16_POLY, be = False):
        self.table = u16.array([0] * A_CRC_SIZ)
        if be:
            self.call = a_crc16be
            a_crc16be_init(<a_u16_t *>self.table.data.as_voidptr, poly)
        else:
            self.call = a_crc16le
            a_crc16le_init(<a_u16_t *>self.table.data.as_voidptr, poly)
    def __call__(self, data: bytes, init: a_u16_t = A_CRC16_INIT) -> a_u16_t:
        return self.call(<a_u16_t *>self.table.data.as_voidptr, <const void *>data, len(data), init)

@cython.wraparound(False)
@cython.boundscheck(False)
cdef class crc32:
    POLY = A_CRC32_POLY
    INIT = A_CRC32_INIT
    cdef array table
    property table:
        def __get__(self):
            return self.table
    cdef a_u32_t (*call)(const a_u32_t *, const void *, a_size_t, a_u32_t)
    def __init__(self, poly: a_u32_t = A_CRC32_POLY, be = False):
        self.table = u32.array([0] * A_CRC_SIZ)
        if be:
            self.call = a_crc32be
            a_crc32be_init(<a_u32_t *>self.table.data.as_voidptr, poly)
        else:
            self.call = a_crc32le
            a_crc32le_init(<a_u32_t *>self.table.data.as_voidptr, poly)
    def __call__(self, data: bytes, init: a_u32_t = A_CRC32_INIT) -> a_u32_t:
        return self.call(<a_u32_t *>self.table.data.as_voidptr, <const void *>data, len(data), init)

@cython.wraparound(False)
@cython.boundscheck(False)
cdef class crc64:
    POLY = A_CRC64_POLY
    INIT = A_CRC64_INIT
    cdef array table
    property table:
        def __get__(self):
            return self.table
    cdef a_u64_t (*call)(const a_u64_t *, const void *, a_size_t, a_u64_t)
    def __init__(self, poly: a_u64_t = A_CRC64_POLY, be = False):
        self.table = u64.array([0] * A_CRC_SIZ)
        if be:
            self.call = a_crc64be
            a_crc64be_init(<a_u64_t *>self.table.data.as_voidptr, poly)
        else:
            self.call = a_crc64le
            a_crc64le_init(<a_u64_t *>self.table.data.as_voidptr, poly)
    def __call__(self, data: bytes, init: a_u64_t = A_CRC64_INIT) -> a_u64_t:
        return self.call(<a_u64_t *>self.table.data.as_voidptr, <const void *>data, len(data), init)
