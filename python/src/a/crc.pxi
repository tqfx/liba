from a.crc cimport *

@cython.wraparound(False)
@cython.boundscheck(False)
cdef class crc8:
    cdef array table
    POLY = A_CRC8_POLY
    INIT = A_CRC8_INIT
    def __cinit__(self, poly: a_u8_t = A_CRC8_POLY, high = False):
        self.table = u8s([0] * A_CRC_SIZ)
        if high:
            a_crc8h_init(<a_u8_t *>self.table.data.as_voidptr, poly)
        else:
            a_crc8l_init(<a_u8_t *>self.table.data.as_voidptr, poly)
    def __call__(self, data: bytes, init: a_u8_t = A_CRC8_INIT) -> a_u8_t:
        return a_crc8(<a_u8_t *>self.table.data.as_voidptr, <const void *>data, len(data), init)
    @property
    def table(self):
        return self.table

ctypedef a_u16_t (*a_crc16_f)(const a_u16_t *, const void *, a_size_t, a_u16_t)

@cython.wraparound(False)
@cython.boundscheck(False)
cdef class crc16:
    cdef a_crc16_f f
    cdef array table
    POLY = A_CRC16_POLY
    INIT = A_CRC16_INIT
    def __cinit__(self, poly: a_u16_t = A_CRC16_POLY, high = False):
        self.table = u16s([0] * A_CRC_SIZ)
        if high:
            self.f = a_crc16h
            a_crc16h_init(<a_u16_t *>self.table.data.as_voidptr, poly)
        else:
            self.f = a_crc16l
            a_crc16l_init(<a_u16_t *>self.table.data.as_voidptr, poly)
    def __call__(self, data: bytes, init: a_u16_t = A_CRC16_INIT) -> a_u16_t:
        return self.f(<a_u16_t *>self.table.data.as_voidptr, <const void *>data, len(data), init)
    @property
    def table(self):
        return self.table

ctypedef a_u32_t (*a_crc32_f)(const a_u32_t *, const void *, a_size_t, a_u32_t)

@cython.wraparound(False)
@cython.boundscheck(False)
cdef class crc32:
    cdef a_crc32_f f
    cdef array table
    POLY = A_CRC32_POLY
    INIT = A_CRC32_INIT
    def __cinit__(self, poly: a_u32_t = A_CRC32_POLY, high = False):
        self.table = u32s([0] * A_CRC_SIZ)
        if high:
            self.f = a_crc32h
            a_crc32h_init(<a_u32_t *>self.table.data.as_voidptr, poly)
        else:
            self.f = a_crc32l
            a_crc32l_init(<a_u32_t *>self.table.data.as_voidptr, poly)
    def __call__(self, data: bytes, init: a_u32_t = A_CRC32_INIT) -> a_u32_t:
        return self.f(<a_u32_t *>self.table.data.as_voidptr, <const void *>data, len(data), init)
    @property
    def table(self):
        return self.table

ctypedef a_u64_t (*a_crc64_f)(const a_u64_t *, const void *, a_size_t, a_u64_t)

@cython.wraparound(False)
@cython.boundscheck(False)
cdef class crc64:
    cdef a_crc64_f f
    cdef array table
    POLY = A_CRC64_POLY
    INIT = A_CRC64_INIT
    def __cinit__(self, poly: a_u64_t = A_CRC64_POLY, high = False):
        self.table = u64s([0] * A_CRC_SIZ)
        if high:
            self.f = a_crc64h
            a_crc64h_init(<a_u64_t *>self.table.data.as_voidptr, poly)
        else:
            self.f = a_crc64l
            a_crc64l_init(<a_u64_t *>self.table.data.as_voidptr, poly)
    def __call__(self, data: bytes, init: a_u64_t = A_CRC64_INIT) -> a_u64_t:
        return self.f(<a_u64_t *>self.table.data.as_voidptr, <const void *>data, len(data), init)
    @property
    def table(self):
        return self.table
