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

NB = -3
NM = -2
NS = -1
ZO = 0
PS = +1
PM = +2
PB = +3

mmp = [
    [a.mf.TRI, NB, NB, NM],
    [a.mf.TRI, NB, NM, NS],
    [a.mf.TRI, NM, NS, ZO],
    [a.mf.TRI, NS, ZO, PS],
    [a.mf.TRI, ZO, PS, PM],
    [a.mf.TRI, PS, PM, PB],
    [a.mf.TRI, PM, PB, PB],
    [a.mf.NUL, ZO, ZO, ZO],
]
mkp = [
    [NB, NB, NM, NM, NS, ZO, ZO],
    [NB, NB, NM, NS, NS, ZO, PS],
    [NM, NM, NM, NS, ZO, PS, PS],
    [NM, NM, NS, ZO, PS, PM, PM],
    [NS, NS, ZO, PS, PS, PM, PM],
    [NS, ZO, PS, PM, PM, PM, PB],
    [ZO, ZO, PM, PM, PM, PB, PB],
]
mki = [
    [PB, PB, PM, PM, PS, ZO, ZO],
    [PB, PB, PM, PS, PS, ZO, ZO],
    [PB, PM, PS, PS, ZO, NS, NS],
    [PM, PM, PS, ZO, NS, NM, NM],
    [PM, PS, ZO, NS, NS, NM, NB],
    [ZO, ZO, NS, NS, NM, NB, NB],
    [ZO, ZO, NS, NM, NM, NB, NB],
]
mkd = [
    [NS, PS, PB, PB, PB, PM, NS],
    [NS, PS, PB, PM, PM, PS, ZO],
    [ZO, PS, PM, PM, PS, PS, ZO],
    [ZO, PS, PS, PS, PS, PS, ZO],
    [ZO, ZO, ZO, ZO, ZO, ZO, ZO],
    [NB, NS, NS, NS, NS, NS, NB],
    [NB, NM, NM, NM, NS, NS, NB],
]

IMIN = -3
IMAX = +3
OMIN = -10
OMAX = +10


def fuzzy(e: float, c: float):
    e = 6 / (IMAX - IMIN) * e
    c = 3 / (IMAX - IMIN) * c

    mmse = []
    idxe = []
    mf = a.mf()
    for idx, param in enumerate(mmp[:-1]):
        ms = mf(param[0], e, param[1:])
        if ms > 0:
            idxe.append(idx)
            mmse.append(ms)
    mmsc = []
    idxc = []
    for idx, param in enumerate(mmp[:-1]):
        ms = mf(param[0], c, param[1:])
        if ms > 0:
            idxc.append(idx)
            mmsc.append(ms)
    if mmse == [] or mmsc == []:
        return 0, 0, 0

    num = 0.0
    joint = []
    for e in mmse:
        row = []
        for c in mmsc:
            y = pow(e * c, 0.5) * pow(1 - (1 - e) * (1 - c), 0.5)
            row.append(y)
            num += y
        joint.append(row)

    kp = 0.0
    for i in range(len(mmse)):
        for j in range(len(mmsc)):
            kp += joint[i][j] * mkp[idxe[i]][idxc[j]]
    ki = 0.0
    for i in range(len(mmse)):
        for j in range(len(mmsc)):
            ki += joint[i][j] * mki[idxe[i]][idxc[j]]
    kd = 0.0
    for i in range(len(mmse)):
        for j in range(len(mmsc)):
            kd += joint[i][j] * mkd[idxe[i]][idxc[j]]

    alpha = (OMAX - OMIN) / 6.0 / num
    kp *= alpha
    ki *= alpha
    kd *= alpha

    return kp, ki, kd


kp = 400
ki = 200
kd = 0.005
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
fpid = a.fpid(2, Ts, mmp, mkp, mki, mkd, IMIN, IMAX, OMIN, OMAX)

r = 1.0
setpoint = [r] * len(data)

title = "Fuzzy Proportional Integral Derivative"

y = 0.0
tf.zero()
error1 = []
feedback1 = []
fpid.kpid(kp, ki, kd)
for i in data:
    u = fpid(r, y)
    y = tf(u)
    feedback1.append(y)
    error1.append(r - y)

s = 0.0
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
    s += (kp + dkp) * x[0] + (ki + dki) * x[1] + (kd + dkd) * x[2]
    u = s
    if u < OMIN:
        u = OMIN
    elif u > OMAX:
        u = OMAX
    y = tf(u)
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
plt.xlabel('time(s)')
plt.grid(True)
plt.savefig(os.path.join(prefix, "fpid.png"))
