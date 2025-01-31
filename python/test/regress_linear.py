#!/usr/bin/env python
from __future__ import print_function
import os, sys

path = os.path.dirname(__file__)
path = os.path.dirname(path)
sys.path.insert(0, path)
if len(sys.argv) > 1:
    sys.stdout = open(sys.argv[1], "w")

import liba  # type: ignore

N = 100
x = liba.new_real([0, 1, 2, 3, 4])
y = liba.new_real([1, 2, 3, 4, 5])

regress = liba.regress_linear([0], 0)

regress.zero()
for i in range(N):
    regress.sgd(x, y, 0.1)
print("y=" + str(regress.coef[0]) + "x+" + str(regress.bias))
print(liba.real_sum(regress.err(x, y)))
print(list(regress.eval(x)))
print(list(regress.err(x, y)))

regress.zero()
for i in range(N):
    regress.bgd(x, y, 0.1)
print("y=" + str(regress.coef[0]) + "x+" + str(regress.bias))
print(liba.real_sum(regress.err(x, y)))
print(list(regress.eval(x)))
print(list(regress.err(x, y)))

regress.zero()
print(regress.mgd(x, y, 0.001, 0.2, 0.1, epoch=N))
print("y=" + str(regress.coef[0]) + "x+" + str(regress.bias))
print(liba.real_sum(regress.err(x, y)))
print(list(regress.eval(x)))
print(list(regress.err(x, y)))

regress.gd(x, 0, 0)

regress.coef = regress.coef
regress.bias = regress.bias
