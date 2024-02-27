#!/usr/bin/env python
import os, sys

sys.path.insert(0, os.getcwd())
prefix = os.path.join(sys.path[0], "build")
if not os.path.exists(prefix):
    os.mkdir(prefix)
try:
    import numpy as np
    import matplotlib.pyplot as plt
except Exception as e:
    print(e)
    exit()

import liba  # type: ignore

Ts = 1.0
f_0 = 1.0
f_e = 1000.0
c = (f_e - f_0) / Ts
T = 1.0 / 10000
t = 0
x = []
while t < Ts:
    x.append(t)
    t += T
x1 = np.array(x)
x2 = np.array(x)
hpf = liba.hpf(10, 0.01)
x1 = np.cos(2 * np.pi * (f_0 * x1 + 0.5 * c * x1 * x1))
for i in range(len(x2)):
    x2[i] = hpf(x2[i])
plt.figure("High Pass Filter")
plt.plot(x, x1, "b-", x, x2, "g-")
plt.savefig(os.path.join(prefix, "hpf.png"))
plt.show()
