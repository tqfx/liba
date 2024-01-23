#!/usr/bin/env python
import os, sys

sys.path.insert(0, os.getcwd())
if len(sys.argv) > 1:
    sys.stdout = open(sys.argv[1], "w")

import liba as a

text = b"0123456789"

crc = a.crc8(0x07)
assert crc.table
assert crc(text) == 0x45

crc = a.crc8(0x31, reversed=True)
assert crc.table
assert crc(text) == 0x75

crc = a.crc16(0x1021)
assert crc.table
assert crc(text) == 0x9C58

crc = a.crc16(0x8005, reversed=True)
assert crc.table
assert crc(text) == 0x443D

crc = a.crc32(0x1EDC6F41)
assert crc.table
assert crc(text) == 0x512B456E

crc = a.crc32(0x04C11DB7, reversed=True)
assert crc.table
assert crc(text) == 0x450EAFB0

crc = a.crc64(0x000000000000001B)
assert crc.table
assert crc(text) == 0xE4FFBEA588AFC790

crc = a.crc64(0x42F0E1EBA9EA3693, reversed=True)
assert crc.table
assert crc(text) == 0xDA60676A5CDE0008
