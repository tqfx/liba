#!/usr/bin/env python
from glob import glob
import os, re

for source in glob(os.path.join("lua/src", "**.c"), recursive=True):
    with open(source, "r", encoding="UTF-8") as f:
        text = text_ = f.read()
    for item in re.findall(r"0x([0-9A-Fa-f]+): // (\w+)", text):
        value = 0
        for i in item[1]:
            value = value * 131 + ord(i)
            value &= 0xFFFFFFFF
        new = "%08X" % value
        if item[0] != new:
            print("{} -> {} // {}".format(item[0], new, item[1]))
            old = "0x{}: // {}".format(item[0], item[1])
            new = "0x{}: // {}".format(new, item[1])
            text = text.replace(old, new)
    if text != text_:
        with open(source, "wb") as f:
            f.write(text.encode("UTF-8"))
