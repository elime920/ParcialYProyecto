import numpy as np
import matplotlib.pyplot as plt
import seaborn as sb   # Special for heat map.
from mpl_toolkits.mplot3d import Axes3D
import matplotlib.colors as colors
import matplotlib.cm as cm
from sys import argv
from matplotlib.colors import BoundaryNorm
from matplotlib.ticker import MaxNLocator


# The data is extracted from the text files.
matrix = np.loadtxt('myOutput2.dat', unpack = True)  # File Matrix
x, y, w = np.loadtxt('Completo.dat', unpack=True)    # File x, y, w.

# ----------------------
# 3D histogram.
# ----------------------

# Set the dimensions
xpos = [range(matrix.shape[0])]
ypos = [range(matrix.shape[1])]
# 
xpos, ypos = np.meshgrid(xpos, ypos)
xpos = xpos.flatten('F')
ypos = ypos.flatten('F')
zpos = np.zeros_like(x)

# width, length, deep.

dx = 0.5 * np.ones_like(zpos)
dy = dx.copy()
dz = matrix.flatten()

#To make a kind of "color map" if the bin is high it is "hotter"

offset = dz + np.abs(dz.min())
fracs = offset.astype(float)/offset.max()
norm = colors.Normalize(fracs.min(), fracs.max())
color_values = cm.jet(norm(fracs.tolist()))


# Heatmap.

fig = plt.figure(figsize=(10, 10))
plt.pcolormesh(matrix,cmap='YlOrRd')
plt.colorbar()

# 3D Histogram

fig = plt.figure(figsize=(40, 10))
ax = fig.add_subplot(121, projection='3d')
ax.bar3d(xpos, ypos, zpos, dx, dy, dz, color=color_values, zsort='average', alpha =0.5)

# Smooth surface

#fig = plt.figure(figsize=(30, 10))
ax1 = fig.add_subplot(122, projection='3d')
surf = ax1.plot_trisurf(x, y, w, cmap=cm.jet, linewidth=0.1)
fig.colorbar(surf, shrink=0.5, aspect=5)


plt.show()
