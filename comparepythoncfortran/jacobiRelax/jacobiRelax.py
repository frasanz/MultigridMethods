#!/usr/bin/python

import numpy as np

h2 = 1.0/2048
u = np.random.rand(2048,2048)
u[0,:]=0.0
u[:,0]=0.0
u[2047,:]=0.0
u[:,2047]=0.0
f = np.ndarray(shape=(2048,2048), dtype=float)
v = np.ndarray(shape=(2048,2048), dtype=float)

print u
print f
for iter in range(1,10):
    for i in range (1,2046):
        for j in range (1,2046):
            v[i,j] = 0.25*(h2 * f[i,j] + u[i-1,j] + u[i+1,j] + u[i,j-1] + u[i,j+1])
    u=v
    print u

