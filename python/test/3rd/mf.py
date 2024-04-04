#!/usr/bin/env python
import os, sys

base = os.path.dirname(__file__)
path = os.path.dirname(base)
path = os.path.dirname(path)
sys.path.insert(0, path)
try:
    import numpy as np
    import matplotlib.pyplot as plt
except Exception as e:
    print(e)
    exit()

import liba  # type: ignore

title = "Gaussian membership function"
x = np.arange(-3, 3, 0.001)
y = liba.mf.gauss(x, 1, 0)
plt.figure(title)
plt.title(title)
plt.plot(x, np.array(y, copy=False))
plt.grid(True)
plt.savefig(os.path.join(base, "mf_gauss.png"))

title = "Gaussian combination membership function"
x = np.arange(-3, 3, 0.001)
y = liba.mf.gauss2(x, 1, -1, 1, +1)
plt.figure(title)
plt.title(title)
plt.plot(x, np.array(y, copy=False))
plt.grid(True)
plt.savefig(os.path.join(base, "mf_gauss2.png"))

title = "Generalized bell-shaped membership function"
x = np.arange(-3, 3, 0.001)
y = liba.mf.gbell(x, 2, 4, 0)
plt.figure(title)
plt.title(title)
plt.plot(x, np.array(y, copy=False))
plt.grid(True)
plt.savefig(os.path.join(base, "mf_gbell.png"))

title = "Sigmoidal membership function"
x = np.arange(-3, 3, 0.001)
y = liba.mf.sig(x, 2, 0)
plt.figure(title)
plt.title(title)
plt.plot(x, np.array(y, copy=False))
plt.grid(True)
plt.savefig(os.path.join(base, "mf_sig.png"))

title = "Difference between two sigmoidal membership functions"
x = np.arange(-3, 3, 0.001)
y = liba.mf.dsig(x, 5, -2, +5, 2)
plt.figure(title)
plt.title(title)
plt.plot(x, np.array(y, copy=False))
plt.grid(True)
plt.savefig(os.path.join(base, "mf_dsig.png"))

title = "Product of two sigmoidal membership functions"
x = np.arange(-3, 3, 0.001)
y = liba.mf.psig(x, 5, -2, -5, 2)
plt.figure(title)
plt.title(title)
plt.plot(x, np.array(y, copy=False))
plt.grid(True)
plt.savefig(os.path.join(base, "mf_psig.png"))

title = "Triangular membership function"
x = np.arange(0, 2, 0.001)
y = liba.mf.tri(x, 0, 1, 2)
plt.figure(title)
plt.title(title)
plt.plot(x, np.array(y, copy=False))
plt.grid(True)
plt.savefig(os.path.join(base, "mf_tri.png"))

y = []
title = "Trapezoidal membership function"
x = np.arange(0, 3, 0.001)
y = liba.mf.trap(x, 0, 1, 2, 3)
plt.figure(title)
plt.title(title)
plt.plot(x, np.array(y, copy=False))
plt.grid(True)
plt.savefig(os.path.join(base, "mf_trap.png"))

title = "Linear s-shaped saturation membership function"
x = np.arange(0, 3, 0.001)
y = liba.mf.lins(x, 1, 2)
plt.figure(title)
plt.title(title)
plt.plot(x, np.array(y, copy=False))
plt.grid(True)
plt.savefig(os.path.join(base, "mf_lins.png"))

title = "Linear z-shaped saturation membership function"
x = np.arange(0, 3, 0.001)
y = liba.mf.linz(x, 1, 2)
plt.figure(title)
plt.title(title)
plt.plot(x, np.array(y, copy=False))
plt.grid(True)
plt.savefig(os.path.join(base, "mf_linz.png"))

title = "S-shaped membership function"
x = np.arange(0, 3, 0.001)
y = liba.mf.s(x, 1, 2)
plt.figure(title)
plt.title(title)
plt.plot(x, np.array(y, copy=False))
plt.grid(True)
plt.savefig(os.path.join(base, "mf_s.png"))

title = "Z-shaped membership function"
x = np.arange(0, 3, 0.001)
y = liba.mf.z(x, 1, 2)
plt.figure(title)
plt.title(title)
plt.plot(x, np.array(y, copy=False))
plt.grid(True)
plt.savefig(os.path.join(base, "mf_z.png"))

y = []
title = "Pi-shaped membership function"
x = np.arange(0, 3, 0.001)
y = liba.mf.pi(x, 0, 1, 2, 3)
plt.figure(title)
plt.title(title)
plt.plot(x, np.array(y, copy=False))
plt.grid(True)
plt.savefig(os.path.join(base, "mf_pi.png"))

S = 1
params = [
    (liba.mf.TRI, -3 * S, -3 * S, -2 * S),
    (liba.mf.TRI, -3 * S, -2 * S, -1 * S),
    (liba.mf.TRI, -2 * S, -1 * S, +0 * S),
    (liba.mf.TRI, -1 * S, +0 * S, +1 * S),
    (liba.mf.TRI, +0 * S, +1 * S, +2 * S),
    (liba.mf.TRI, +1 * S, +2 * S, +3 * S),
    (liba.mf.TRI, +2 * S, +3 * S, +3 * S),
]

title = "membership function"
x = np.arange(-3 * S, +3 * S, 0.001)
plt.figure(title)
plt.title(title)
for param in params:
    plt.plot(x, np.array(liba.mf()(param[0], x, param[1:]), copy=False))
plt.savefig(os.path.join(base, "mf.png"))
plt.show()
