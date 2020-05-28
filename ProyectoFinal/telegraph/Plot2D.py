import numpy as np
import matplotlib.pyplot as plt

# The data is extracted from the text files.
matrix = np.loadtxt('outputMatrix.dat', unpack = True)  # File Matrix
t, z, w = np.loadtxt('outputCols.dat', unpack=True)    # File x, y, w.

# endpoints

t0 = np.amin(t)
tf = np.amax(t)
z0 = np.amin(z)
zf = np.amax(z)

# Number of points

NT = len(matrix[0])
NZ = len(matrix)

# array for t and z.

tarr = np.linspace(t0, tf, NT)
zarr = np.linspace(z0, zf, NZ)

# figure z vs approximations

fig = plt.figure()
for i in range(NZ):
    plt.plot(zarr,matrix[:,i])
    plt.xlabel('z(m)')
    plt.ylabel('w')
plt.savefig('ExerciseCONST_2D.png')


plt.show()
