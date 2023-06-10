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


def polytrack3_formula(k):
    text_p = "p="
    if k[0]:
        text_p += "%g" % (k[0])
    if k[1]:
        text_p += "%+g%s" % (k[1], "t")
    if k[2]:
        text_p += "%+g%s" % (k[2], "t^2")
    if k[3]:
        text_p += "%+g%s" % (k[3], "t^3")
    text_v = "v="
    if k[1]:
        text_v += "%g" % (k[1])
    if k[2]:
        text_v += "%+g%s" % (k[2] * 2, "t")
    if k[3]:
        text_v += "%+g%s" % (k[3] * 3, "t^2")
    text_a = "a="
    if k[2]:
        text_a += "%g" % (k[2] * 2)
    if k[3]:
        text_a += "%+g%s" % (k[3] * 6, "t")
    return (
        text_p.replace("=+", "="),
        text_v.replace("=+", "="),
        text_a.replace("=+", "="),
    )


def polytrack5_formula(k):
    text_p = "p="
    if k[0]:
        text_p += "%g" % (k[0])
    if k[1]:
        text_p += "%+g%s" % (k[1], "t")
    if k[2]:
        text_p += "%+g%s" % (k[2], "t^2")
    if k[3]:
        text_p += "%+g%s" % (k[3], "t^3")
    if k[4]:
        text_p += "%+g%s" % (k[4], "t^4")
    if k[5]:
        text_p += "%+g%s" % (k[5], "t^5")
    text_v = "v="
    if k[1]:
        text_v += "%g" % (k[1])
    if k[2]:
        text_v += "%+g%s" % (k[2] * 2, "t")
    if k[3]:
        text_v += "%+g%s" % (k[3] * 3, "t^2")
    if k[4]:
        text_v += "%+g%s" % (k[4] * 4, "t^3")
    if k[5]:
        text_v += "%+g%s" % (k[5] * 5, "t^4")
    text_a = "a="
    if k[2]:
        text_a += "%g" % (k[2] * 2)
    if k[3]:
        text_a += "%+g%s" % (k[3] * 6, "t")
    if k[4]:
        text_a += "%+g%s" % (k[4] * 12, "t^2")
    if k[5]:
        text_a += "%+g%s" % (k[3] * 20, "t^3")
    return (
        text_p.replace("=+", "="),
        text_v.replace("=+", "="),
        text_a.replace("=+", "="),
    )


def polytrack7_formula(k):
    text_p = "p="
    if k[0]:
        text_p += "%g" % (k[0])
    if k[1]:
        text_p += "%+g%s" % (k[1], "t")
    if k[2]:
        text_p += "%+g%s" % (k[2], "t^2")
    if k[3]:
        text_p += "%+g%s" % (k[3], "t^3")
    if k[4]:
        text_p += "%+g%s" % (k[4], "t^4")
    if k[5]:
        text_p += "%+g%s" % (k[5], "t^5")
    if k[6]:
        text_p += "%+g%s" % (k[6], "t^6")
    if k[7]:
        text_p += "%+g%s" % (k[7], "t^7")
    text_v = "v="
    if k[1]:
        text_v += "%g" % (k[1])
    if k[2]:
        text_v += "%+g%s" % (k[2] * 2, "t")
    if k[3]:
        text_v += "%+g%s" % (k[3] * 3, "t^2")
    if k[4]:
        text_v += "%+g%s" % (k[4] * 4, "t^3")
    if k[5]:
        text_v += "%+g%s" % (k[5] * 5, "t^4")
    if k[6]:
        text_v += "%+g%s" % (k[6] * 6, "t^5")
    if k[7]:
        text_v += "%+g%s" % (k[7] * 7, "t^6")
    text_a = "a="
    if k[2]:
        text_a += "%g" % (k[2] * 2)
    if k[3]:
        text_a += "%+g%s" % (k[3] * 6, "t")
    if k[4]:
        text_a += "%+g%s" % (k[4] * 12, "t^2")
    if k[5]:
        text_a += "%+g%s" % (k[3] * 20, "t^3")
    if k[6]:
        text_a += "%+g%s" % (k[6] * 30, "t^4")
    if k[7]:
        text_a += "%+g%s" % (k[7] * 42, "t^5")
    text_j = "j="
    if k[3]:
        text_j += "%g" % (k[3] * 6)
    if k[4]:
        text_j += "%+g%s" % (k[4] * 12, "t")
    if k[5]:
        text_j += "%+g%s" % (k[3] * 60, "t^2")
    if k[6]:
        text_j += "%+g%s" % (k[6] * 120, "t^3")
    if k[7]:
        text_j += "%+g%s" % (k[7] * 210, "t^4")
    return (
        text_p.replace("=+", "="),
        text_v.replace("=+", "="),
        text_a.replace("=+", "="),
        text_j.replace("=+", "="),
    )


t = (0, 1)
q = (0, 1)
v = (0, 1)
data = np.arange(t[0], t[1], 0.01)

track = a.polytrack3(t[0], t[1], q[0], q[1], v[0], v[1])
label = polytrack3_formula(track.k)
plt.figure("3 polynomial trajectory")

plt.subplot(311)
plt.title("cubic polynomial trajectory")
plt.ylabel("Position")
plt.plot(data, track.pos(data), "r-", label=label[0])
plt.legend()

plt.subplot(312)
plt.ylabel("Velocity")
plt.plot(data, track.vel(data), "b-", label=label[1])
plt.legend()

plt.subplot(313)
plt.ylabel("Acceleration")
plt.plot(data, track.acc(data), "g-", label=label[2])
plt.legend()

plt.xlabel("t")
plt.savefig(os.path.join(prefix, "trajectory_polynomial_3.png"))

(pos, vel, acc) = track(data)
plt.figure("all 3 polynomial trajectory")

plt.subplot(311)
plt.title("all cubic polynomial trajectory")
plt.ylabel("Position")
plt.plot(data, pos, "r-", label=label[0])
plt.legend()

plt.subplot(312)
plt.ylabel("Velocity")
plt.plot(data, vel, "b-", label=label[1])
plt.legend()

plt.subplot(313)
plt.ylabel("Acceleration")
plt.plot(data, acc, "g-", label=label[2])
plt.legend()

plt.xlabel("t")
plt.savefig(os.path.join(prefix, "trajectory_polynomial_3a.png"))

track = a.polytrack5(t[0], t[1], q[0], q[1], v[0], v[1])
label = polytrack5_formula(track.k)
plt.figure("5 polynomial trajectory")

plt.subplot(311)
plt.title("quintic polynomial trajectory")
plt.ylabel("Position")
plt.plot(data, track.pos(data), "r-", label=label[0])
plt.legend()

plt.subplot(312)
plt.ylabel("Velocity")
plt.plot(data, track.vel(data), "b-", label=label[1])
plt.legend()

plt.subplot(313)
plt.ylabel("Acceleration")
plt.plot(data, track.acc(data), "g-", label=label[2])
plt.legend()

plt.xlabel("t")
plt.savefig(os.path.join(prefix, "trajectory_polynomial_5.png"))

(pos, vel, acc) = track(data)
plt.figure("all 5 polynomial trajectory")

plt.subplot(311)
plt.title("all quintic polynomial trajectory")
plt.ylabel("Position")
plt.plot(data, pos, "r-", label=label[0])
plt.legend()

plt.subplot(312)
plt.ylabel("Velocity")
plt.plot(data, vel, "b-", label=label[1])
plt.legend()

plt.subplot(313)
plt.ylabel("Acceleration")
plt.plot(data, acc, "g-", label=label[2])
plt.legend()

plt.xlabel("t")
plt.savefig(os.path.join(prefix, "trajectory_polynomial_5a.png"))

track = a.polytrack7(t[0], t[1], q[0], q[1], v[0], v[1])
label = polytrack7_formula(track.k)
plt.figure("7 polynomial trajectory")

plt.subplot(411)
plt.title("hepta polynomial trajectory")
plt.ylabel("Position")
plt.plot(data, track.pos(data), "r-", label=label[0])
plt.legend()

plt.subplot(412)
plt.ylabel("Velocity")
plt.plot(data, track.vel(data), "b-", label=label[1])
plt.legend()

plt.subplot(413)
plt.ylabel("Acceleration")
plt.plot(data, track.acc(data), "g-", label=label[2])
plt.legend()

plt.subplot(414)
plt.ylabel("Jerk")
plt.plot(data, track.jer(data), "k-", label=label[3])
plt.legend()

plt.xlabel("t")
plt.savefig(os.path.join(prefix, "trajectory_polynomial_7.png"))

(pos, vel, acc, jer) = track(data)
plt.figure("all 7 polynomial trajectory")

plt.subplot(411)
plt.title("all hepta polynomial trajectory")
plt.ylabel("Position")
plt.plot(data, pos, "r-", label=label[0])
plt.legend()

plt.subplot(412)
plt.ylabel("Velocity")
plt.plot(data, vel, "b-", label=label[1])
plt.legend()

plt.subplot(413)
plt.ylabel("Acceleration")
plt.plot(data, acc, "g-", label=label[2])
plt.legend()

plt.subplot(414)
plt.ylabel("Jerk")
plt.plot(data, jer, "k-", label=label[3])
plt.legend()

plt.xlabel("t")
plt.savefig(os.path.join(prefix, "trajectory_polynomial_7a.png"))
