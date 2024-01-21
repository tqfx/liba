#!/usr/bin/env python
import os, sys

sys.path.insert(0, os.getcwd())
if len(sys.argv) > 1:
    sys.stdout = open(sys.argv[1], "w")

import liba as a

text = b"123456789"

crc = a.crc8(0x31)
print(crc(text))
crc.table

crc = a.crc8(0x8C, reversed=True)
print(crc(text))
crc.table

crc = a.crc16(0x8005)
print(crc(text))
crc.table

crc = a.crc16(0xA001, reversed=True)
print(crc(text))
crc.table

crc = a.crc32(0x04C11DB7)
print(crc(text))
crc.table

crc = a.crc32(0xEDB88320, reversed=True)
print(crc(text))
crc.table

crc = a.crc64(0x42F0E1EBA9EA3693)
print(crc(text))
crc.table

crc = a.crc64(0xC96C5795D7870F42, reversed=True)
print(crc(text))
crc.table
