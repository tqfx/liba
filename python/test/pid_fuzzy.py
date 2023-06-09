#!/usr/bin/env python
import os, sys

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

S = 1
NB = -3 * S
NM = -2 * S
NS = -1 * S
ZO = +0 * S
PS = +1 * S
PM = +2 * S
PB = +3 * S
me = [
    [a.mf.TRI, NB, NB, NM],
    [a.mf.TRI, NB, NM, NS],
    [a.mf.TRI, NM, NS, ZO],
    [a.mf.TRI, NS, ZO, PS],
    [a.mf.TRI, ZO, PS, PM],
    [a.mf.TRI, PS, PM, PB],
    [a.mf.TRI, PM, PB, PB],
]
NB = -6 * S
NM = -4 * S
NS = -2 * S
ZO = +0 * S
PS = +2 * S
PM = +4 * S
PB = +6 * S
mec = [
    [a.mf.TRI, NB, NB, NM],
    [a.mf.TRI, NB, NM, NS],
    [a.mf.TRI, NM, NS, ZO],
    [a.mf.TRI, NS, ZO, PS],
    [a.mf.TRI, ZO, PS, PM],
    [a.mf.TRI, PS, PM, PB],
    [a.mf.TRI, PM, PB, PB],
]
S = 10 / 3
NB = -3 * S
NM = -2 * S
NS = -1 * S
ZO = +0 * S
PS = +1 * S
PM = +2 * S
PB = +3 * S
mkp = [
    [NB, NB, NM, NM, NS, ZO, ZO],
    [NB, NB, NM, NS, NS, ZO, PS],
    [NM, NM, NM, NS, ZO, PS, PS],
    [NM, NM, NS, ZO, PS, PM, PM],
    [NS, NS, ZO, PS, PS, PM, PM],
    [NS, ZO, PS, PM, PM, PM, PB],
    [ZO, ZO, PM, PM, PM, PB, PB],
]
S = 0.01 / 3
NB = -3 * S
NM = -2 * S
NS = -1 * S
ZO = +0 * S
PS = +1 * S
PM = +2 * S
PB = +3 * S
mki = [
    [PB, PB, PM, PM, PS, ZO, ZO],
    [PB, PB, PM, PS, PS, ZO, ZO],
    [PB, PM, PS, PS, ZO, NS, NS],
    [PM, PM, PS, ZO, NS, NM, NM],
    [PM, PS, ZO, NS, NS, NM, NB],
    [ZO, ZO, NS, NS, NM, NB, NB],
    [ZO, ZO, NS, NM, NM, NB, NB],
]
S = 0.1 / 3
NB = -3 * S
NM = -2 * S
NS = -1 * S
ZO = +0 * S
PS = +1 * S
PM = +2 * S
PB = +3 * S
mkd = [
    [NS, PS, PB, PB, PB, PM, NS],
    [NS, PS, PB, PM, PM, PS, ZO],
    [ZO, PS, PM, PM, PS, PS, ZO],
    [ZO, PS, PS, PS, PS, PS, ZO],
    [ZO, ZO, ZO, ZO, ZO, ZO, ZO],
    [NB, NS, NS, NS, NS, NS, NB],
    [NB, NM, NM, NM, NS, NS, NB],
]


def fuzzy(e: float, c: float):
    mf = a.mf()

    idxe = []
    vale = []
    for idx, param in enumerate(me[:-1]):
        ms = mf(param[0], e, param[1:])
        if ms > 0:
            idxe.append(idx)
            vale.append(ms)
    if idxe == []:
        return 0, 0, 0

    idxec = []
    valec = []
    for idx, param in enumerate(me[:-1]):
        ms = mf(param[0], c, param[1:])
        if ms > 0:
            idxec.append(idx)
            valec.append(ms)
    if idxec == []:
        return 0, 0, 0

    inv = 0.0
    joint = []
    for e in vale:
        row = []
        for c in valec:
            y = pow(e * c, 0.5) * pow(1 - (1 - e) * (1 - c), 0.5)
            row.append(y)
            inv += y
        joint.append(row)
    inv = 1 / inv

    kp = 0.0
    for i in range(len(vale)):
        for j in range(len(valec)):
            kp += joint[i][j] * mkp[idxe[i]][idxec[j]]
    kp *= inv
    ki = 0.0
    for i in range(len(vale)):
        for j in range(len(valec)):
            ki += joint[i][j] * mki[idxe[i]][idxec[j]]
    ki *= inv
    kd = 0.0
    for i in range(len(vale)):
        for j in range(len(valec)):
            kd += joint[i][j] * mkd[idxe[i]][idxec[j]]
    kd *= inv

    return kp, ki, kd


kp = 9
ki = 0.01
kd = 0.1
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


MIN = -10
MAX = +10
tf = a.tf(num, den[1:])
pid_fuzzy = a.pid_fuzzy(2, Ts, me, mec, mkp, mki, mkd, MIN, MAX)

r = 1.0
setpoint = [r] * len(data)

title = "Fuzzy Proportional Integral Derivative"

y = 0.0
tf.zero()
error1 = []
feedback1 = []
pid_fuzzy.kpid(kp, ki, kd)
for i in data:
    y = pid_fuzzy(r, y)
    y = tf(y)
    feedback1.append(y)
    error1.append(r - y)

u = 0.0
y = 0.0
tf.zero()
e = [0.0, 0.0, 0.0]
x = [0.0, 0.0, 0.0]
error2 = []
feedback2 = []
for i in data:
    e = np.roll(e, 1)
    e[0] = r - y
    x[0] = e[0] - e[1]
    x[1] = e[0] * Ts
    x[2] = (e[0] + e[2] - e[1] * 2) / Ts
    dkp, dki, dkd = fuzzy(e[0], e[0] - e[1])
    u += (kp + dkp) * x[0] + (ki + dki) * x[1] + (kd + dkd) * x[2]
    y = u
    if y < MIN:
        y = MIN
    elif y > MAX:
        y = MAX
    y = tf(y)
    feedback2.append(y)
    error2.append(r - y)

plt.figure(title)
plt.subplot(211)
plt.title(title)
plt.plot(data, setpoint, "r-", data, feedback1, "b-", data, feedback2, "g-")
plt.ylabel("r - y")
plt.grid(True)
plt.subplot(212)
plt.plot(data, error1, "b-", data, error2, "g-")
plt.ylabel("error")
plt.xlabel("time(s)")
plt.grid(True)
plt.savefig(os.path.join(prefix, "pid_fuzzy.png"))
