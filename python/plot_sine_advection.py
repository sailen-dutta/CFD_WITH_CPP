import numpy as np
import matplotlib.pyplot as plt
from pathlib import Path

project = Path(__file__).resolve().parent.parent

num_file = project / "build" / "apps" / "output" / "solution_0040.csv"
exact_file = project / "build" / "apps" / "output" / "exact_solution_final.csv"

x_num, u_num = np.loadtxt(num_file, delimiter=",", skiprows=1, unpack=True)
x_exact, u_exact = np.loadtxt(exact_file, delimiter=",", skiprows=1, unpack=True)

plt.plot(x_exact, u_exact, label="Exact")
plt.plot(x_num, u_num, label="Numerical")
plt.title("1D Advection: Upwind Scheme")
plt.xlabel("x")
plt.ylabel("u(x,t)")
plt.legend()
plt.grid(True)
plt.show()