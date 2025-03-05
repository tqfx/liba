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

t = (0, 1)
p = (0, 1)
v = (0, 1)
traj = liba.trajpoly7(t[1] - t[0], p[0], p[1], v[0], v[1])
data = np.arange(t[0], t[1], (t[1] - t[0]) / 1000)

text_p = "p="
if traj.c0[0]:
    text_p += "%g" % (traj.c0[0])
if traj.c0[1]:
    text_p += "%+g%s" % (traj.c0[1], "t")
if traj.c0[2]:
    text_p += "%+g%s" % (traj.c0[2], "t^2")
if traj.c0[3]:
    text_p += "%+g%s" % (traj.c0[3], "t^3")
if traj.c0[4]:
    text_p += "%+g%s" % (traj.c0[4], "t^4")
if traj.c0[5]:
    text_p += "%+g%s" % (traj.c0[5], "t^5")
if traj.c0[6]:
    text_p += "%+g%s" % (traj.c0[6], "t^6")
if traj.c0[7]:
    text_p += "%+g%s" % (traj.c0[7], "t^7")
text_p = text_p.replace("=+", "=")

text_v = "v="
if traj.c1[0]:
    text_v += "%g" % (traj.c1[0])
if traj.c1[1]:
    text_v += "%+g%s" % (traj.c1[1], "t")
if traj.c1[2]:
    text_v += "%+g%s" % (traj.c1[2], "t^2")
if traj.c1[3]:
    text_v += "%+g%s" % (traj.c1[3], "t^3")
if traj.c1[4]:
    text_v += "%+g%s" % (traj.c1[4], "t^4")
if traj.c1[5]:
    text_v += "%+g%s" % (traj.c1[5], "t^5")
if traj.c1[6]:
    text_v += "%+g%s" % (traj.c1[6], "t^6")
text_v = text_v.replace("=+", "=")

text_a = "a="
if traj.c2[0]:
    text_a += "%g" % (traj.c2[0])
if traj.c2[1]:
    text_a += "%+g%s" % (traj.c2[1], "t")
if traj.c2[2]:
    text_a += "%+g%s" % (traj.c2[2], "t^2")
if traj.c2[3]:
    text_a += "%+g%s" % (traj.c2[3], "t^3")
if traj.c2[4]:
    text_a += "%+g%s" % (traj.c2[4], "t^4")
if traj.c2[5]:
    text_a += "%+g%s" % (traj.c2[5], "t^5")
text_a = text_a.replace("=+", "=")

text_j = "j="
if traj.c3[0]:
    text_j += "%g" % (traj.c3[0])
if traj.c3[1]:
    text_j += "%+g%s" % (traj.c3[1], "t")
if traj.c3[2]:
    text_j += "%+g%s" % (traj.c3[2], "t^2")
if traj.c3[3]:
    text_j += "%+g%s" % (traj.c3[3], "t^3")
if traj.c3[4]:
    text_j += "%+g%s" % (traj.c3[4], "t^4")
text_j = text_j.replace("=+", "=")

plt.figure("7 polynomial trajectory")

plt.subplot(411)
plt.title("hepta polynomial trajectory")
plt.ylabel("Position")
plt.plot(data, np.array(traj.pos(data), copy=False), "r-", label=text_p)
plt.legend()

plt.subplot(412)
plt.ylabel("Velocity")
plt.plot(data, np.array(traj.vel(data), copy=False), "b-", label=text_v)
plt.legend()

plt.subplot(413)
plt.ylabel("Acceleration")
plt.plot(data, np.array(traj.acc(data), copy=False), "g-", label=text_a)
plt.legend()

plt.subplot(414)
plt.ylabel("Jerk")
plt.plot(data, np.array(traj.jer(data), copy=False), "k-", label=text_j)
plt.legend()

plt.xlabel("t")
plt.savefig(os.path.join(base, "trajectory_polynomial_7.png"))
plt.show()
