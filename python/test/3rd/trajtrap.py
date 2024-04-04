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

traj = liba.trajtrap()
traj.gen(2, 2, -2, 0, 4)
data = np.arange(0, traj.t, traj.t / 1000)

plt.figure("trapezoidal velocity trajectory")

plt.subplot(311)
plt.title("trapezoidal velocity trajectory")
plt.ylabel("Position")
plt.plot(data, np.array(traj.pos(data), copy=False), "r-", label="q")
plt.legend()

plt.subplot(312)
plt.ylabel("Velocity")
plt.plot(data, np.array(traj.vel(data), copy=False), "b-", label="v")
plt.legend()

plt.subplot(313)
plt.ylabel("Acceleration")
plt.plot(data, np.array(traj.acc(data), copy=False), "g-", label="a")
plt.legend()

plt.xlabel("t")
plt.savefig(os.path.join(base, "trajectory_trapezoidal.png"))
plt.show()
