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

traj = a.traptraj(10, 2, 2, -2)
data = np.arange(0, traj.t, 0.01)
plt.figure("trapezoidal velocity profile trajectory")

plt.subplot(311)
plt.title("trapezoidal velocity profile trajectory")
plt.ylabel("Position")
plt.plot(data, traj.pos(data), "r-", label="q")
plt.legend()

plt.subplot(312)
plt.ylabel("Velocity")
plt.plot(data, traj.vel(data), "b-", label="v")
plt.legend()

plt.subplot(313)
plt.ylabel("Acceleration")
plt.plot(data, traj.acc(data), "g-", label="a")
plt.legend()

plt.xlabel("t")
plt.savefig(os.path.join(prefix, "trapezoidal_trajectory.png"))
