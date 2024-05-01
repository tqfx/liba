#!/usr/bin/env python
import os, sys, argparse

parser = argparse.ArgumentParser()
parser.add_argument("src")
parser.add_argument("dst")
args = parser.parse_known_args()

with open(args[0].src, "r") as f:
    text = f.read()

cur = "#if defined(A_HAVE_H)"
dir = os.path.dirname(args[0].dst)
src = os.path.basename(args[0].src)
dst = os.path.basename(args[0].dst)
new = '#include "{}"\n{}'.format(dst, cur)
res = text.replace(cur, new)
new = os.path.join(dir, src)

if res != text:
    with open(new, "wb") as f:
        f.write(res.encode())

dir = os.path.dirname(args[0].src)
res = os.path.relpath(args[0].dst, dir)
res = res.replace("\\", "/")
sys.stdout.write(res)
