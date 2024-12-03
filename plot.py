import numpy as np
import matplotlib.pyplot as plt

n = int(input())
theta = np.linspace(0, 2*np.pi, n)
data = []
for i in range(n):
    data.append(float(input()))
r = np.array(data)
r = np.log10(r)*10

plt.polar(theta, r)

plt.show()
