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

t = (0, 1)
q = (0, 1)
v = (0, 1)
data = np.arange(t[0], t[1], 0.01)
traj = a.trajpoly7(t[1] - t[0], q[0], q[1], v[0], v[1])
text_p = "p="
if traj.q[0]:
    text_p += "%g" % (traj.q[0])
if traj.q[1]:
    text_p += "%+g%s" % (traj.q[1], "t")
if traj.q[2]:
    text_p += "%+g%s" % (traj.q[2], "t^2")
if traj.q[3]:
    text_p += "%+g%s" % (traj.q[3], "t^3")
if traj.q[4]:
    text_p += "%+g%s" % (traj.q[4], "t^4")
if traj.q[5]:
    text_p += "%+g%s" % (traj.q[5], "t^5")
if traj.q[6]:
    text_p += "%+g%s" % (traj.q[6], "t^6")
if traj.q[7]:
    text_p += "%+g%s" % (traj.q[7], "t^7")
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
if traj.v[5]:
    text_v += "%+g%s" % (traj.v[5], "t^5")
if traj.v[6]:
    text_v += "%+g%s" % (traj.v[6], "t^6")
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
if traj.a[4]:
    text_a += "%+g%s" % (traj.a[4], "t^4")
if traj.a[5]:
    text_a += "%+g%s" % (traj.a[5], "t^5")
text_a = text_a.replace("=+", "=")
text_j = "j="
if traj.j[0]:
    text_j += "%g" % (traj.j[0])
if traj.j[1]:
    text_j += "%+g%s" % (traj.j[1], "t")
if traj.j[2]:
    text_j += "%+g%s" % (traj.j[2], "t^2")
if traj.j[3]:
    text_j += "%+g%s" % (traj.j[3], "t^3")
if traj.j[4]:
    text_j += "%+g%s" % (traj.j[4], "t^4")
text_j = text_j.replace("=+", "=")
plt.figure("7 polynomial trajectory")

plt.subplot(411)
plt.title("hepta polynomial trajectory")
plt.ylabel("Position")
plt.plot(data, traj.pos(data), "r-", label=text_p)
plt.legend()

plt.subplot(412)
plt.ylabel("Velocity")
plt.plot(data, traj.vel(data), "b-", label=text_v)
plt.legend()

plt.subplot(413)
plt.ylabel("Acceleration")
plt.plot(data, traj.acc(data), "g-", label=text_a)
plt.legend()

plt.subplot(414)
plt.ylabel("Jerk")
plt.plot(data, traj.jer(data), "k-", label=text_j)
plt.legend()

plt.xlabel("t")
plt.savefig(os.path.join(prefix, "trajectory_polynomial_7.png"))
