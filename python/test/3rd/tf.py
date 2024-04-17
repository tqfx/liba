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


class TF:
    def num_get(self):
        return self.num_

    def num_set(self, num):
        self.num_ = np.array(num, dtype=float)
        self.input = np.zeros(len(num), dtype=float)

    num = property(num_get, num_set, None, None)

    def den_get(self):
        return den

    def den_set(self, den):
        self.den_ = np.array(den, dtype=float)
        self.output = np.zeros(len(den), dtype=float)

    den = property(den_get, den_set, None, None)

    def __init__(self, num, den):
        self.num = num
        self.den = den

    def __call__(self, input: float) -> float:
        self.input = np.roll(self.input, 1)
        self.input[0] = input  # type: ignore
        output = self.num_ @ self.input - self.den_ @ self.output  # type: ignore
        self.output = np.roll(self.output, 1)
        self.output[0] = output  # type: ignore
        return output


Ts = 0.001
try:
    import control.matlab as ct

    sysc = ct.tf(133, [1, 25, 0])
    sysd = ct.c2d(sysc, Ts)
    print(sysc, sysd)

    [[num]], [[den]] = ct.tfdata(sysd)
except ModuleNotFoundError:
    num = [6.59492796e-05, 6.54019884e-05]
    den = [1.0, -1.97530991, 0.97530991]
except Exception as e:
    print(e)
    exit()
import liba  # type: ignore

tf = liba.tf(num, den[1:])
tf_ = TF(num, den[1:])

x = np.arange(0, 0.5, Ts)
y = x.copy()
z = x.copy()
for i in range(len(x)):
    y[i] = tf_(x[i])
    z[i] = tf(x[i])

plt.plot(x, y, "r-", x, z, "b-")
plt.savefig(os.path.join(base, "tf.png"))
plt.xlabel("t")
plt.show()
