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
except Exception as e:
    print(e)
    exit()


class TF:
    def __init__(self, num, den) -> None:
        self.num = num
        self.den = den

    def __call__(self, u: float) -> float:
        self._u = np.roll(self._u, 1)
        self._u[0] = u  # type: ignore
        v = self._num @ self._u - self._den @ self._v  # type: ignore
        self._v = np.roll(self._v, 1)
        self._v[0] = v  # type: ignore
        return v

    @property
    def num(self):
        return self._num

    @num.setter
    def num(self, num):
        self._num = np.array(num, dtype=float)
        self._u = np.array(len(self._num) * [0.0], dtype=float)

    @property
    def den(self):
        return self._den

    @den.setter
    def den(self, den):
        self._den = np.array(den, dtype=float)
        self._v = np.array(len(self._den) * [0.0], dtype=float)


Ts = 0.001
data = np.arange(0, 0.2, Ts)

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

tf = a.tf(num, den[1:])
tf_ = TF(num, den[1:])

for t in data:
    t = t * 1000
    tf_(t)
    tf(t)
print(tf_.num, tf_.den)
print(tf.num, tf.den)
