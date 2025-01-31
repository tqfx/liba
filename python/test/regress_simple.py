#!/usr/bin/env python
from __future__ import print_function
import os, sys

path = os.path.dirname(__file__)
path = os.path.dirname(path)
sys.path.insert(0, path)
if len(sys.argv) > 1:
    sys.stdout = open(sys.argv[1], "w")

import liba  # type: ignore

x = liba.new_real([0, 1, 2, 3, 4])
y = liba.new_real([1, 2, 3, 4, 5])

regress = liba.regress_simple()

regress.ols_(x, y, 2, 3)
print(list(regress.evar(y)))
print(list(regress.eval(x)))
regress.zero()

regress.olsx(x, y, 2)
print(list(regress.evar(y)))
print(list(regress.eval(x)))
regress.zero()

regress.olsy(x, y, 3)
print(list(regress.evar(y)))
print(list(regress.eval(x)))
regress.zero()

regress.ols(x, y)
print(list(regress.evar(y)))
print(list(regress.eval(x)))
regress.zero()

regress.coef = regress.coef
regress.bias = regress.bias
