#!/usr/bin/env python
from __future__ import print_function
import os, sys

path = os.path.dirname(__file__)
path = os.path.dirname(path)
sys.path.insert(0, path)
if len(sys.argv) > 1:
    sys.stdout = open(sys.argv[1], "w")

import liba  # type: ignore

N = 1000
T = 6 / N
x = liba.new_real(N)
for i in range(N):
    x[i] = (i - N / 2) * T

liba.mf.gauss(x, 1, 0)
liba.mf.gauss2(x, 1, -1, 1, +1)
liba.mf.gbell(x, 2, 4, 0)
liba.mf.sig(x, 2, 0)
liba.mf.dsig(x, 5, -2, +5, 2)
liba.mf.psig(x, 5, -2, -5, 2)
liba.mf.tri(x, 0, 1, 2)
liba.mf.trap(x, 0, 1, 2, 3)
liba.mf.lins(x, 1, 2)
liba.mf.linz(x, 1, 2)
liba.mf.s(x, 1, 2)
liba.mf.z(x, 1, 2)
liba.mf.pi(x, 0, 1, 2, 3)

S = 1
params = [
    liba.new_real((liba.mf.TRI, -3 * S, -3 * S, -2 * S)),
    liba.new_real((liba.mf.TRI, -3 * S, -2 * S, -1 * S)),
    liba.new_real((liba.mf.TRI, -2 * S, -1 * S, +0 * S)),
    liba.new_real((liba.mf.TRI, -1 * S, +0 * S, +1 * S)),
    liba.new_real((liba.mf.TRI, +0 * S, +1 * S, +2 * S)),
    liba.new_real((liba.mf.TRI, +1 * S, +2 * S, +3 * S)),
    liba.new_real((liba.mf.TRI, +2 * S, +3 * S, +3 * S)),
]
for param in params:
    liba.mf.mf(param[0], x, param[1:])
