#!/usr/bin/env python
from __future__ import print_function
import os, sys

path = os.path.dirname(__file__)
path = os.path.dirname(path)
sys.path.insert(0, path)

import liba  # type: ignore

a = liba.new_real([1, 2, 3])
print(list(a), liba.poly_eval(2, a))
print(list(a), list(liba.poly_eval(a, a)))
print(list(a), liba.poly_evar(2, a))
print(list(a), list(liba.poly_evar(a, a)))
