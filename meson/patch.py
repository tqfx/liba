#!/usr/bin/env python
import os, argparse

parser = argparse.ArgumentParser()
parser.add_argument("src")
parser.add_argument("dst")
args = parser.parse_known_args()

if args[0].dst:
    with open(args[0].dst, "r") as f:
        text = f.read()

    cur = "#if defined(A_HAVE_H)"
    dir = os.path.dirname(args[0].src)
    src = os.path.basename(args[0].src)
    dst = os.path.basename(args[0].dst)
    new = '#include "{}"\n{}'.format(src, cur)
    text = text.replace(cur, new)

    with open(os.path.join(dir, dst), "wb") as f:
        f.write(text.encode())
