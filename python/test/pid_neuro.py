#!/usr/bin/env python
import os, sys

path = os.path.dirname(__file__)
path = os.path.dirname(path)
sys.path.insert(0, path)
if len(sys.argv) > 1:
    sys.stdout = open(sys.argv[1], "w")

import liba  # type: ignore

Ts = 0.001

k = 4000
kp = 4
ki = 0.04
kd = 1.0
wp = 1
wi = 0
wd = 0

num = [6.59492796e-05, 6.54019884e-05]
den = [1.0, -1.97530991, 0.97530991]

tf = liba.tf(num, den[1:])
pid_neuro = liba.pid_neuro().kpid(k, kp, ki, kd).wpid(wp, wi, wd)

t = 0
x = []
while t <= 0.2:
    x.append(t)
    t += Ts

r = 1
y = 0
for i in range(len(x)):
    y = tf(pid_neuro.inc(r, y))
    print("%g,%g" % (x[i], y))

pid_neuro.k = pid_neuro.k
pid_neuro.kp = pid_neuro.kp
pid_neuro.ki = pid_neuro.ki
pid_neuro.kd = pid_neuro.kd
pid_neuro.wp = pid_neuro.wp
pid_neuro.wi = pid_neuro.wi
pid_neuro.wd = pid_neuro.wd
pid_neuro.outmax = pid_neuro.outmax
pid_neuro.outmin = pid_neuro.outmin
pid_neuro.out
pid_neuro.fdb
pid_neuro.err
pid_neuro.ec
