#!/usr/bin/env python
import os, sys

base = os.path.dirname(__file__)
path = os.path.dirname(base)
sys.path.insert(0, path)

import liba  # type: ignore

k = [1, 2, 3]
print(k, liba.poly_eval(2, *k))
print(k, list(liba.poly_eval(k, *k)))
print(k, liba.poly_evar(2, *k))
print(k, list(liba.poly_evar(k, *k)))
