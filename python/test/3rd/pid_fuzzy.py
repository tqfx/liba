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

X = 1
NL = -3 * X
NM = -2 * X
NS = -1 * X
ZO = +0 * X
PS = +1 * X
PM = +2 * X
PL = +3 * X
me = [
    liba.new_float([liba.mf.TRI, NL, NL, NM]),
    liba.new_float([liba.mf.TRI, NL, NM, NS]),
    liba.new_float([liba.mf.TRI, NM, NS, ZO]),
    liba.new_float([liba.mf.TRI, NS, ZO, PS]),
    liba.new_float([liba.mf.TRI, ZO, PS, PM]),
    liba.new_float([liba.mf.TRI, PS, PM, PL]),
    liba.new_float([liba.mf.TRI, PM, PL, PL]),
]
NL = -6 * X
NM = -4 * X
NS = -2 * X
ZO = +0 * X
PS = +2 * X
PM = +4 * X
PL = +6 * X
mec = [
    liba.new_float([liba.mf.TRI, NL, NL, NM]),
    liba.new_float([liba.mf.TRI, NL, NM, NS]),
    liba.new_float([liba.mf.TRI, NM, NS, ZO]),
    liba.new_float([liba.mf.TRI, NS, ZO, PS]),
    liba.new_float([liba.mf.TRI, ZO, PS, PM]),
    liba.new_float([liba.mf.TRI, PS, PM, PL]),
    liba.new_float([liba.mf.TRI, PM, PL, PL]),
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


def fuzzy(e: float, ec: float):
    idx_e = []
    val_e = []
    for idx, param in enumerate(me):
        ms = liba.mf.mf(param[0], e, param[1:])
        if ms > 0:
            idx_e.append(idx)
            val_e.append(ms)
    if idx_e == []:
        return 0, 0, 0

    idx_ec = []
    val_ec = []
    for idx, param in enumerate(mec):
        ms = liba.mf.mf(param[0], ec, param[1:])
        if ms > 0:
            idx_ec.append(idx)
            val_ec.append(ms)
    if idx_ec == []:
        return 0, 0, 0

    inv = 0
    mat = []
    for e in val_e:
        row = []
        for ec in val_ec:
            y = (e * ec) ** 0.5 * (1 - (1 - e) * (1 - ec)) ** 0.5
            row.append(y)
            inv += y
        mat.append(row)
    inv = 1 / inv

    kp = 0.0
    for i in range(len(val_e)):
        for ii in range(len(val_ec)):
            kp += mat[i][ii] * mkp[idx_e[i]][idx_ec[ii]]
    kp *= inv
    ki = 0.0
    for i in range(len(val_e)):
        for ii in range(len(val_ec)):
            ki += mat[i][ii] * mki[idx_e[i]][idx_ec[ii]]
    ki *= inv
    kd = 0.0
    for i in range(len(val_e)):
        for ii in range(len(val_ec)):
            kd += mat[i][ii] * mkd[idx_e[i]][idx_ec[ii]]
    kd *= inv

    return kp, ki, kd


Ts = 0.001
kp = 9
ki = 0.01 * Ts
kd = 0.1 / Ts
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
tf = liba.tf(num, den[1:])
pid_fuzzy = (
    liba.pid_fuzzy()
    .set_opr(liba.pid_fuzzy.CAP_ALGEBRA)
    .set_rule(me, mec, mkp, mki, mkd)
    .set_nfuzz(2)
)
pid_fuzzy.outmax = MAX
pid_fuzzy.outmin = MIN

r = 1.0
setpoint = [r] * len(data)

title = "Fuzzy Proportional Integral Derivative"

y = 0.0
tf.zero()
error1 = []
feedback1 = []
pid_fuzzy.set_kpid(kp, ki, kd)
for i in data:
    y = pid_fuzzy.inc(r, y)
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
    x[1] = e[0]
    x[2] = e[0] - e[1] * 2 + e[2]
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
plt.savefig(os.path.join(base, "pid_fuzzy.png"))
plt.show()
