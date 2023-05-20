#!/usr/bin/env python
import sys
import os

sys.path.insert(0, os.getcwd())
prefix = os.path.join(sys.path[0], "build")
if not os.path.exists(prefix):
    os.mkdir(prefix)
try:
    import liba as a
    import numpy as np
    import matplotlib.pyplot as plt
except Exception as e:
    print(e)
    exit()

title = "Gaussian membership function"
x = np.arange(-3, 3, 0.001)
y = a.mf.gauss(x, 1, 0)
plt.figure(title)
plt.title(title)
plt.plot(x, y)
plt.grid(True)
plt.savefig(os.path.join(prefix, "mf_gauss.png"))

title = "Generalized bell-shaped membership function"
x = np.arange(-3, 3, 0.001)
y = a.mf.gbell(x, 2, 1, 0)
plt.figure(title)
plt.title(title)
plt.plot(x, y)
plt.grid(True)
plt.savefig(os.path.join(prefix, "mf_gbell.png"))

title = "Sigmoidal membership function"
x = np.arange(-3, 3, 0.001)
y = a.mf.sig(x, 2, 0)
plt.figure(title)
plt.title(title)
plt.plot(x, y)
plt.grid(True)
plt.savefig(os.path.join(prefix, "mf_sig.png"))

title = "Triangular membership function"
x = np.arange(0, 2, 0.001)
y = a.mf.tri(x, 0, 1, 2)
plt.figure(title)
plt.title(title)
plt.plot(x, y)
plt.grid(True)
plt.savefig(os.path.join(prefix, "mf_tri.png"))

y = []
title = "Trapezoidal membership function"
x = np.arange(0, 3, 0.001)
y = a.mf.trap(x, 0, 1, 2, 3)
plt.figure(title)
plt.title(title)
plt.plot(x, y)
plt.grid(True)
plt.savefig(os.path.join(prefix, "mf_trap.png"))

title = "Z-shaped membership function"
x = np.arange(0, 3, 0.001)
y = a.mf.z(x, 1, 2)
plt.figure(title)
plt.title(title)
plt.plot(x, y)
plt.grid(True)
plt.savefig(os.path.join(prefix, "mf_z.png"))

S = 1
params = [
    (a.mf.TRI, -3 * S, -3 * S, -2 * S),
    (a.mf.TRI, -3 * S, -2 * S, -1 * S),
    (a.mf.TRI, -2 * S, -1 * S, +0 * S),
    (a.mf.TRI, -1 * S, +0 * S, +1 * S),
    (a.mf.TRI, +0 * S, +1 * S, +2 * S),
    (a.mf.TRI, +1 * S, +2 * S, +3 * S),
    (a.mf.TRI, +2 * S, +3 * S, +3 * S),
]

title = "membership function"
x = np.arange(-3 * S, +3 * S, 0.001)
plt.figure(title)
plt.title(title)
for param in params:
    plt.plot(x, a.mf()(param[0], x, param[1:]))
plt.savefig(os.path.join(prefix, "mf.png"))
