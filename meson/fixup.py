#!/usr/bin/env python
import os, argparse

parser = argparse.ArgumentParser()
parser.add_argument("src")
parser.add_argument("dst")
args = parser.parse_known_args()

if args[0].dst:
    with open(args[0].dst, "r") as f:
        text = f.read()

    old = "#if defined(A_HAVE_H)"
    dst = os.path.dirname(args[0].src)
    src = os.path.basename(args[0].src)
    new = '#include "{}"\n{}'.format(src, old)
    text = text.replace(old, new)

    with open(os.path.join(dst, os.path.basename(args[0].dst)), "wb") as f:
        f.write(text.encode())
