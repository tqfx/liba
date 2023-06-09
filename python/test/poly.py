#!/usr/bin/env python
import os, sys

sys.path.insert(0, os.getcwd())

import liba as a

k = [1, 2, 3]
print(k, a.poly_eval(k, *k))
print(k, a.poly_eval(2, *k))
print(k, a.poly_evar(k, *k))
print(k, a.poly_evar(2, *k))
