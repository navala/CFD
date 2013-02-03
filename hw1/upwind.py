#!/usr/bin/env python

import sys,math
from pylab import *
import matplotlib.pyplot as plt

name = "advection_v0_M100"
f = open("%s.dat"%(name), 'r')
lines = f.readlines()
x0 = []
y0 = []
for line in lines:
    yvalues = [float(l) for l in line.split()]
    x0.append(yvalues[0]); y0.append(yvalues[1])

name = "advection_v1_M50"
f = open("%s.dat"%(name), 'r')
lines = f.readlines()
x1 = []
y1 = []
for line in lines:
    yvalues = [float(l) for l in line.split()]
    x1.append(yvalues[0]); y1.append(yvalues[1])

name = "advection_v1_M100"
f = open("%s.dat"%(name), 'r')
lines = f.readlines()
x2 = []
y2 = []
for line in lines:
    yvalues = [float(l) for l in line.split()]
    x2.append(yvalues[0]); y2.append(yvalues[1])

name = "advection_v1_M200"
f = open("%s.dat"%(name), 'r')
lines = f.readlines()
x3 = []
y3 = []
for line in lines:
    yvalues = [float(l) for l in line.split()]
    x3.append(yvalues[0]); y3.append(yvalues[1])


name = "advection_v1_M400"
f = open("%s.dat"%(name), 'r')
lines = f.readlines()
x4 = []
y4 = []
for line in lines:
    yvalues = [float(l) for l in line.split()]
    x4.append(yvalues[0]); y4.append(yvalues[1])

plt.subplot(1,4,1)
plt.ylim(-0.0,1.0)
plt.plot(x0,y0,ls="dashed")
plt.plot(x1,y1,ls="solid")

plt.subplot(1,4,2)
plt.ylim(-0.0,1.0)
plt.plot(x0,y0,ls="dashed")
plt.plot(x2,y2,ls="solid")

plt.subplot(1,4,3)
plt.ylim(-0.0,1.0)
plt.plot(x0,y0,ls="dashed")
plt.plot(x3,y3,ls="solid")


plt.subplot(1,4,4)
plt.ylim(-0.0,1.0)
plt.plot(x0,y0,ls="dashed")
plt.plot(x4,y4,ls="solid")

plt.savefig("upwind.eps")
plt.show()
