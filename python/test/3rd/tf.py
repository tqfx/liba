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


class TF:
    def num_get(self):
        return self._num

    def num_set(self, num):
        self._num = np.array(num, dtype=float)
        self.input = np.array(len(num) * [0.0], dtype=float)

    num = property(num_get, num_set, None, None)

    def den_get(self):
        return den

    def den_set(self, den):
        self._den = np.array(den, dtype=float)
        self.output = np.array(len(den) * [0.0], dtype=float)

    den = property(den_get, den_set, None, None)

    def __init__(self, num, den):
        self.num = num
        self.den = den

    def __call__(self, input: float) -> float:
        self.input = np.roll(self.input, 1)
        self.input[0] = input  # type: ignore
        output = self._num @ self.input - self._den @ self.output  # type: ignore
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
plt.savefig(os.path.join(prefix, "tf.png"))
plt.xlabel("t")
plt.show()
