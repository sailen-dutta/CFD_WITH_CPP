import numpy as np
import matplotlib.pyplot as plt

x, u = np.loadtxt("solution.csv", delimiter=",", skiprows=1, unpack=True)

plt.step(x,u,where='mid')
plt.plot(x,u,'o')
plt.xlabel("x")
plt.ylabel("y")
plt.grid(True)
plt.show()