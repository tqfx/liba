from a cimport *

cdef extern from "a/hash.h":
    a_u32 a_hash_bkdr(const char *str, a_u32 val) nogil
    a_u32 a_hash_sdbm(const char *str, a_u32 val) nogil
