#!/usr/bin/env python
'''
 @file polytrack.py
 @brief Testing polynomial trajectory
 @copyright Copyright (C) 2020 tqfx, All rights reserved.
'''
import os
import sys

sys.path.insert(0, os.getcwd())
prefix = os.path.join(sys.path[0], "build")
if not os.path.exists(prefix):
    os.mkdir(prefix)
try:
    import a
    import numpy as np
    import matplotlib.pyplot as plt
except Exception as e:
    print(e)
    exit()

t = (0, 1)
q = (0, 1)
data = np.arange(t[0], t[1], 0.01)
source = (t[0], q[0], 0, 0, 0)
target = (t[1], q[1], 1, 1, 1)

track = a.polytrack3(source, target)
label = track.text()
plt.figure("3 polynomial trajectory")

plt.subplot(311)
plt.title("cubic polynomial trajectory")
plt.ylabel("Position")
plt.plot(data, track.pos(data), "r-", label=label[0])
plt.legend()

plt.subplot(312)
plt.ylabel("Velocity")
plt.plot(data, track.vec(data), "b-", label=label[1])
plt.legend()

plt.subplot(313)
plt.ylabel("Acceleration")
plt.plot(data, track.acc(data), "g-", label=label[2])
plt.legend()

plt.xlabel('t')
plt.savefig(os.path.join(prefix, "trajectory_polynomial_3.png"))

(pos, vec, acc) = track(data)
plt.figure("all 3 polynomial trajectory")

plt.subplot(311)
plt.title("all cubic polynomial trajectory")
plt.ylabel("Position")
plt.plot(data, pos, "r-", label=label[0])
plt.legend()

plt.subplot(312)
plt.ylabel("Velocity")
plt.plot(data, vec, "b-", label=label[1])
plt.legend()

plt.subplot(313)
plt.ylabel("Acceleration")
plt.plot(data, acc, "g-", label=label[2])
plt.legend()

plt.xlabel('t')
plt.savefig(os.path.join(prefix, "trajectory_polynomial_3a.png"))

track = a.polytrack5(source, target)
label = track.text()
plt.figure("5 polynomial trajectory")

plt.subplot(311)
plt.title("quintic polynomial trajectory")
plt.ylabel("Position")
plt.plot(data, track.pos(data), "r-", label=label[0])
plt.legend()

plt.subplot(312)
plt.ylabel("Velocity")
plt.plot(data, track.vec(data), "b-", label=label[1])
plt.legend()

plt.subplot(313)
plt.ylabel("Acceleration")
plt.plot(data, track.acc(data), "g-", label=label[2])
plt.legend()

plt.xlabel('t')
plt.savefig(os.path.join(prefix, "trajectory_polynomial_5.png"))

(pos, vec, acc) = track(data)
plt.figure("all 5 polynomial trajectory")

plt.subplot(311)
plt.title("all quintic polynomial trajectory")
plt.ylabel("Position")
plt.plot(data, pos, "r-", label=label[0])
plt.legend()

plt.subplot(312)
plt.ylabel("Velocity")
plt.plot(data, vec, "b-", label=label[1])
plt.legend()

plt.subplot(313)
plt.ylabel("Acceleration")
plt.plot(data, acc, "g-", label=label[2])
plt.legend()

plt.xlabel('t')
plt.savefig(os.path.join(prefix, "trajectory_polynomial_5a.png"))

track = a.polytrack7(source, target)
label = track.text()
plt.figure("7 polynomial trajectory")

plt.subplot(411)
plt.title("hepta polynomial trajectory")
plt.ylabel("Position")
plt.plot(data, track.pos(data), "r-", label=label[0])
plt.legend()

plt.subplot(412)
plt.ylabel("Velocity")
plt.plot(data, track.vec(data), "b-", label=label[1])
plt.legend()

plt.subplot(413)
plt.ylabel("Acceleration")
plt.plot(data, track.acc(data), "g-", label=label[2])
plt.legend()

plt.subplot(414)
plt.ylabel("Jerk")
plt.plot(data, track.jer(data), "k-", label=label[3])
plt.legend()

plt.xlabel('t')
plt.savefig(os.path.join(prefix, "trajectory_polynomial_7.png"))

(pos, vec, acc, jer) = track(data)
plt.figure("all 7 polynomial trajectory")

plt.subplot(411)
plt.title("all hepta polynomial trajectory")
plt.ylabel("Position")
plt.plot(data, pos, "r-", label=label[0])
plt.legend()

plt.subplot(412)
plt.ylabel("Velocity")
plt.plot(data, vec, "b-", label=label[1])
plt.legend()

plt.subplot(413)
plt.ylabel("Acceleration")
plt.plot(data, acc, "g-", label=label[2])
plt.legend()

plt.subplot(414)
plt.ylabel("Jerk")
plt.plot(data, jer, "k-", label=label[3])
plt.legend()

plt.xlabel('t')
plt.savefig(os.path.join(prefix, "trajectory_polynomial_7a.png"))
