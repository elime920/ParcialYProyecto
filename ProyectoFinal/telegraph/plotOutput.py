#!/usr/bin/env python

#libraries
import numpy as np
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation

#load matrix file
t, z, wV = np.loadtxt("outputCols.dat", unpack = True)
matrix = np.loadtxt("outputMatrix.dat", unpack = True)

#initial and final values, and size of data (depends on NT and NZ written in example1.h)
t0 = np.amin(t)
tf = np.amax(t)
z0 = np.amin(z)
zf = np.amax(z)
NT = len(matrix[0])
NZ = len(matrix)

#minimum an maximum values of the voltaje, to adjust the plot
minV = np.amin(wV)
maxV = np.amax(wV)

#numpy arrays to plot
tarr = np.linspace(t0, tf, NT)
zarr = np.linspace(z0, zf, NZ)
w = np.array_split(np.array(wV), NT)

#Generate all figures as png, then externally merge them as a gif
'''
for i in range(0, NT):
  plt.plot(zarr, w[i], label = "time: %.3f s"%tarr[i])
  plt.legend(loc = 'upper right')
  plt.ylim(minV, maxV)
  plt.grid()
  plt.savefig("fig%03d.png"%i)
  plt.clf() #clear plot
'''

#Export to gif without generating a bunch of images
#Structure taken from a web example
fig, ax = plt.subplots()
plotvar, = plt.plot([], [], 'r-')
time_text = ax.text(0.5, 0.95, '', transform=ax.transAxes)

def init():
  ax.set_xlim(z0, zf)
  ax.set_ylim(minV, maxV)
  ax.set_xlabel(r"$z\ (m)$")
  ax.set_ylabel(r"$w$")
  ax.grid()
  
def update(i):
  plotvar.set_data(zarr, w[i])
  time_text.set_text("Transmission line, t = %.3f s"%(tarr[i]))
  
ani = FuncAnimation(fig, update, range(0, NT), init_func = init)
ani.save("animation.gif", writer = 'imagemagick', fps = 20)
