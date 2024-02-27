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

import liba  # type: ignore

t = (0, 1)
p = (0, 1)
v = (0, 1)
traj = liba.trajpoly5(t[1] - t[0], p[0], p[1], v[0], v[1])
data = np.arange(t[0], t[1], (t[1] - t[0]) / 1000)

text_p = "p="
if traj.p[0]:
    text_p += "%g" % (traj.p[0])
if traj.p[1]:
    text_p += "%+g%s" % (traj.p[1], "t")
if traj.p[2]:
    text_p += "%+g%s" % (traj.p[2], "t^2")
if traj.p[3]:
    text_p += "%+g%s" % (traj.p[3], "t^3")
if traj.p[4]:
    text_p += "%+g%s" % (traj.p[4], "t^4")
if traj.p[5]:
    text_p += "%+g%s" % (traj.p[5], "t^5")
text_p = text_p.replace("=+", "=")

text_v = "v="
if traj.v[0]:
    text_v += "%g" % (traj.v[0])
if traj.v[1]:
    text_v += "%+g%s" % (traj.v[1], "t")
if traj.v[2]:
    text_v += "%+g%s" % (traj.v[2], "t^2")
if traj.v[3]:
    text_v += "%+g%s" % (traj.v[3], "t^3")
if traj.v[4]:
    text_v += "%+g%s" % (traj.v[4], "t^4")
text_v = text_v.replace("=+", "=")

text_a = "a="
if traj.a[0]:
    text_a += "%g" % (traj.a[0])
if traj.a[1]:
    text_a += "%+g%s" % (traj.a[1], "t")
if traj.a[2]:
    text_a += "%+g%s" % (traj.a[2], "t^2")
if traj.a[3]:
    text_a += "%+g%s" % (traj.a[3], "t^3")
text_a = text_a.replace("=+", "=")

plt.figure("5 polynomial trajectory")

plt.subplot(311)
plt.title("puintic polynomial trajectory")
plt.ylabel("Position")
plt.plot(data, traj.pos(data), "r-", label=text_p)
plt.legend()

plt.subplot(312)
plt.ylabel("Velocity")
plt.plot(data, traj.vel(data), "b-", label=text_v)
plt.legend()

plt.subplot(313)
plt.ylabel("Acceleration")
plt.plot(data, traj.acc(data), "g-", label=text_a)
plt.legend()

plt.xlabel("t")
plt.savefig(os.path.join(prefix, "trajectory_polynomial_5.png"))
plt.show()
