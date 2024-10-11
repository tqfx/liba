#!/usr/bin/env python
from __future__ import print_function
import os, sys

path = os.path.dirname(__file__)
path = os.path.dirname(path)
sys.path.insert(0, path)
if len(sys.argv) > 1:
    sys.stdout = open(sys.argv[1], "w")

import liba  # type: ignore

num = [6.59492796e-05, 6.54019884e-05]
den = [1.0, -1.97530991, 0.97530991]

tf = liba.tf(num, den[1:])

N = 1000
T = 0.5 / N
x = liba.new_float(N)
for i in range(N):
    x[i] = i * T

y = liba.new_float(N)
for i in range(N):
    y[i] = tf(x[i])

for i in range(N):
    print("%g,%g" % (x[i], y[i]))

tf.num = tf.num
tf.den = tf.den
tf.input
tf.output
