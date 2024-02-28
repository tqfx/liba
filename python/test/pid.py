#!/usr/bin/env python
import os, sys

sys.path.insert(0, os.getcwd())
if len(sys.argv) > 1:
    sys.stdout = open(sys.argv[1], "w")

import liba  # type: ignore

Ts = 0.001
MIN = -10
MAX = +10

kp = 10.0
ki = 0.01 * Ts
kd = 0.24 / Ts

num = [6.59492796e-05, 6.54019884e-05]
den = [1.0, -1.97530991, 0.97530991]

tf = liba.tf(num, den[1:])
pid = liba.pid().kpid(kp, ki, kd)
pid.outmax = MAX
pid.outmin = MIN

t = 0
x = []
while t <= 0.2:
    x.append(t)
    t += Ts
N = len(x)
r = 1

y1 = [0.0] * N
for i in range(len(x)):
    y1[i] = tf(pid.pos(r, tf.output[0]))

pid.zero()
tf.zero()

y2 = [0.0] * N
for i in range(len(x)):
    y2[i] = tf(pid.inc(r, tf.output[0]))

for i in range(len(x)):
    print("%g,%g,%g,%g" % (x[i], r, y1[i], y2[i]))

pid.kp = pid.kp
pid.ki = pid.ki
pid.kd = pid.kd
pid.summax = pid.summax
pid.summin = pid.summin
pid.sum
pid.outmax = pid.outmax
pid.outmin = pid.outmin
pid.out
pid.fdb
pid.err
