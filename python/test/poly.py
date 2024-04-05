#!/usr/bin/env python
import os, sys

base = os.path.dirname(__file__)
path = os.path.dirname(base)
sys.path.insert(0, path)

import liba  # type: ignore

a = liba.new_num([1, 2, 3])
print(list(a), liba.poly_eval(2, a))
print(list(a), list(liba.poly_eval(a, a)))
print(list(a), liba.poly_evar(2, a))
print(list(a), list(liba.poly_evar(a, a)))
