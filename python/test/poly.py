#!/usr/bin/env python
import os, sys

sys.path.insert(0, os.getcwd())

import liba  # type: ignore

k = [1, 2, 3]
print(k, liba.poly_eval(k, *k))
print(k, liba.poly_eval(2, *k))
print(k, liba.poly_evar(k, *k))
print(k, liba.poly_evar(2, *k))
