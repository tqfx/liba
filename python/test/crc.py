#!/usr/bin/env python
import os, sys

sys.path.insert(0, os.getcwd())
if len(sys.argv) > 1:
    sys.stdout = open(sys.argv[1], "w")

import liba as a

crc = a.crc8()
print(crc(b""))
crc.table

crc = a.crc8(be=True)
print(crc(b""))
crc.table

crc = a.crc16()
print(crc(b""))
crc.table

crc = a.crc16(be=True)
print(crc(b""))
crc.table

crc = a.crc32()
print(crc(b""))
crc.table

crc = a.crc32(be=True)
print(crc(b""))
crc.table

crc = a.crc64()
print(crc(b""))
crc.table

crc = a.crc64(be=True)
print(crc(b""))
crc.table
