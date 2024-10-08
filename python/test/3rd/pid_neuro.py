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

Ts = 0.001
k = 4000
kp = 4
ki = 0.04
kd = 1.0
wp = 1
wi = 0
wd = 0
data = np.arange(0, 0.1, Ts)

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

tf = liba.tf(num, den[1:])
pid_neuro = liba.pid_neuro()

r = 1.0
setpoint = [r] * len(data)

title = "Single Neuron Proportional Integral Derivative"

y = 0.0
tf.zero()
error1 = []
feedback1 = []
pid_neuro.set_kpid(k, kp, ki, kd).set_wpid(wp, wi, wd)
for i in data:
    y = pid_neuro.inc(r, y)
    y = tf(y)
    feedback1.append(y)
    error1.append(r - y)

plt.figure(title)
plt.subplot(211)
plt.title(title)
plt.plot(data, setpoint, "r-", data, feedback1, "b-")
plt.ylabel("r - y")
plt.grid(True)
plt.subplot(212)
plt.plot(data, error1, "b-")
plt.ylabel("error")
plt.xlabel("time(s)")
plt.grid(True)
plt.savefig(os.path.join(base, "pid_neuro.png"))
plt.show()
