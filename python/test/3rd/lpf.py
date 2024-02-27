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

x = np.arange(0, np.pi * 10, np.pi * 0.1)
x1 = np.sin(x) + 0.2 * (np.random.random(len(x)) - 0.5)
x2 = x1.copy()
lpf = liba.lpf(10, 0.01)
for i in range(len(x2)):
    x2[i] = lpf(x2[i])
plt.figure("Low Pass Filter")
plt.plot(x, x1, "b-", x, x2, "g-")
plt.savefig(os.path.join(prefix, "lpf.png"))
plt.show()
