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
    def __init__(self, poly: a_u8 = A_CRC8_POLY, big_endian = False):
        self.table = array_u8([0] * A_CRC_SIZ)
        if big_endian:
            a_crc8be_init(<a_u8 *>self.table.data.as_voidptr, poly)
        else:
            a_crc8le_init(<a_u8 *>self.table.data.as_voidptr, poly)
    def __call__(self, data: bytes, init: a_u8 = A_CRC8_INIT) -> a_u8:
        return a_crc8(<a_u8 *>self.table.data.as_voidptr, <const void *>data, len(data), init)

@cython.wraparound(False)
@cython.boundscheck(False)
cdef class crc16:
    POLY = A_CRC16_POLY
    INIT = A_CRC16_INIT
    cdef array table
    property table:
        def __get__(self):
            return self.table
    cdef a_u16 (*call)(const a_u16 *, const void *, a_size, a_u16)
    def __init__(self, poly: a_u16 = A_CRC16_POLY, big_endian = False):
        self.table = array_u16([0] * A_CRC_SIZ)
        if big_endian:
            self.call = a_crc16be
            a_crc16be_init(<a_u16 *>self.table.data.as_voidptr, poly)
        else:
            self.call = a_crc16le
            a_crc16le_init(<a_u16 *>self.table.data.as_voidptr, poly)
    def __call__(self, data: bytes, init: a_u16 = A_CRC16_INIT) -> a_u16:
        return self.call(<a_u16 *>self.table.data.as_voidptr, <const void *>data, len(data), init)

@cython.wraparound(False)
@cython.boundscheck(False)
cdef class crc32:
    POLY = A_CRC32_POLY
    INIT = A_CRC32_INIT
    cdef array table
    property table:
        def __get__(self):
            return self.table
    cdef a_u32 (*call)(const a_u32 *, const void *, a_size, a_u32)
    def __init__(self, poly: a_u32 = A_CRC32_POLY, big_endian = False):
        self.table = array_u32([0] * A_CRC_SIZ)
        if big_endian:
            self.call = a_crc32be
            a_crc32be_init(<a_u32 *>self.table.data.as_voidptr, poly)
        else:
            self.call = a_crc32le
            a_crc32le_init(<a_u32 *>self.table.data.as_voidptr, poly)
    def __call__(self, data: bytes, init: a_u32 = A_CRC32_INIT) -> a_u32:
        return self.call(<a_u32 *>self.table.data.as_voidptr, <const void *>data, len(data), init)

@cython.wraparound(False)
@cython.boundscheck(False)
cdef class crc64:
    POLY = A_CRC64_POLY
    INIT = A_CRC64_INIT
    cdef array table
    property table:
        def __get__(self):
            return self.table
    cdef a_u64 (*call)(const a_u64 *, const void *, a_size, a_u64)
    def __init__(self, poly: a_u64 = A_CRC64_POLY, big_endian = False):
        self.table = array_u64([0] * A_CRC_SIZ)
        if big_endian:
            self.call = a_crc64be
            a_crc64be_init(<a_u64 *>self.table.data.as_voidptr, poly)
        else:
            self.call = a_crc64le
            a_crc64le_init(<a_u64 *>self.table.data.as_voidptr, poly)
    def __call__(self, data: bytes, init: a_u64 = A_CRC64_INIT) -> a_u64:
        return self.call(<a_u64 *>self.table.data.as_voidptr, <const void *>data, len(data), init)
