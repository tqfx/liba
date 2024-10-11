#!/usr/bin/env python
from __future__ import print_function
import os, sys

path = os.path.dirname(__file__)
path = os.path.dirname(path)
sys.path.insert(0, path)
if len(sys.argv) > 1:
    sys.stdout = open(sys.argv[1], "w")

import liba  # type: ignore

X = 1
NL = -3 * X
NM = -2 * X
NS = -1 * X
ZO = +0 * X
PS = +1 * X
PM = +2 * X
PL = +3 * X
me = [
    [liba.mf.TRI, NL, NL, NM],
    [liba.mf.TRI, NL, NM, NS],
    [liba.mf.TRI, NM, NS, ZO],
    [liba.mf.TRI, NS, ZO, PS],
    [liba.mf.TRI, ZO, PS, PM],
    [liba.mf.TRI, PS, PM, PL],
    [liba.mf.TRI, PM, PL, PL],
]
NL = -6 * X
NM = -4 * X
NS = -2 * X
ZO = +0 * X
PS = +2 * X
PM = +4 * X
PL = +6 * X
mec = [
    [liba.mf.TRI, NL, NL, NM],
    [liba.mf.TRI, NL, NM, NS],
    [liba.mf.TRI, NM, NS, ZO],
    [liba.mf.TRI, NS, ZO, PS],
    [liba.mf.TRI, ZO, PS, PM],
    [liba.mf.TRI, PS, PM, PL],
    [liba.mf.TRI, PM, PL, PL],
]
X = 10 / 3
NL = -3 * X
NM = -2 * X
NS = -1 * X
ZO = +0 * X
PS = +1 * X
PM = +2 * X
PL = +3 * X
mkp = [
    [NL, NL, NM, NM, NS, ZO, ZO],
    [NL, NL, NM, NS, NS, ZO, PS],
    [NM, NM, NM, NS, ZO, PS, PS],
    [NM, NM, NS, ZO, PS, PM, PM],
    [NS, NS, ZO, PS, PS, PM, PM],
    [NS, ZO, PS, PM, PM, PM, PL],
    [ZO, ZO, PM, PM, PM, PL, PL],
]
X = 0.01 / 3
NL = -3 * X
NM = -2 * X
NS = -1 * X
ZO = +0 * X
PS = +1 * X
PM = +2 * X
PL = +3 * X
mki = [
    [PL, PL, PM, PM, PS, ZO, ZO],
    [PL, PL, PM, PS, PS, ZO, ZO],
    [PL, PM, PS, PS, ZO, NS, NS],
    [PM, PM, PS, ZO, NS, NM, NM],
    [PM, PS, ZO, NS, NS, NM, NL],
    [ZO, ZO, NS, NS, NM, NL, NL],
    [ZO, ZO, NS, NM, NM, NL, NL],
]
X = 0.1 / 3
NL = -3 * X
NM = -2 * X
NS = -1 * X
ZO = +0 * X
PS = +1 * X
PM = +2 * X
PL = +3 * X
mkd = [
    [NS, PS, PL, PL, PL, PM, NS],
    [NS, PS, PL, PM, PM, PS, ZO],
    [ZO, PS, PM, PM, PS, PS, ZO],
    [ZO, PS, PS, PS, PS, PS, ZO],
    [ZO, ZO, ZO, ZO, ZO, ZO, ZO],
    [NL, NS, NS, NS, NS, NS, NL],
    [NL, NM, NM, NM, NS, NS, NL],
]

Ts = 0.001
MIN = -10
MAX = +10

kp = 9
ki = 0.01 * Ts
kd = 0.1 / Ts

num = [6.59492796e-05, 6.54019884e-05]
den = [1.0, -1.97530991, 0.97530991]

tf = liba.tf(num, den[1:])
pid_fuzzy = (
    liba.pid_fuzzy()
    .set_opr(liba.pid_fuzzy.CAP_ALGEBRA)
    .set_rule(me, mec, mkp, mki, mkd)
    .set_nfuzz(2)
)
pid_fuzzy.outmax = MAX
pid_fuzzy.outmin = MIN

t = 0
x = []
while t <= 0.2:
    x.append(t)
    t += Ts
N = len(x)
r = 1

y1 = liba.new_float(N)
for i in range(len(x)):
    y1[i] = tf(pid_fuzzy.pos(r, tf.output[0]))

pid_fuzzy.zero()
tf.zero()

y2 = liba.new_float(N)
for i in range(len(x)):
    y2[i] = tf(pid_fuzzy.inc(r, tf.output[0]))

for i in range(len(x)):
    print("%g,%g,%g,%g" % (x[i], r, y1[i], y2[i]))

pid_fuzzy.me
pid_fuzzy.mec
pid_fuzzy.mkp
pid_fuzzy.mki
pid_fuzzy.mkd
pid_fuzzy.kp = pid_fuzzy.kp
pid_fuzzy.ki = pid_fuzzy.ki
pid_fuzzy.kd = pid_fuzzy.kd
pid_fuzzy.summax = pid_fuzzy.summax
pid_fuzzy.summin = pid_fuzzy.summin
pid_fuzzy.sum
pid_fuzzy.outmax = pid_fuzzy.outmax
pid_fuzzy.outmin = pid_fuzzy.outmin
pid_fuzzy.out
pid_fuzzy.fdb
pid_fuzzy.err
pid_fuzzy.me
pid_fuzzy.mec
pid_fuzzy.mkp
pid_fuzzy.mki
pid_fuzzy.mkd
pid_fuzzy.nrule
pid_fuzzy.nfuzz = pid_fuzzy.nfuzz + 1
