import glob
import math
import matplotlib.pyplot as plt
import numpy as np

# Simulation parameters
dt = 0.005
output_frequency = 10
c = 1.0

# Square pulse parameters
pulse_start = 0.4
pulse_end = 0.6
pulse_value = 1.0

# Square pulse exact solution
def exact_square_pulse(x, t, c):
    # Shift pulse using periodic BC
    x_shift = (x - c * t) % 1.0
    
    u_exact = np.zeros_like(x)

    mask = ((x_shift >= pulse_start) & (x_shift <= pulse_end))
    u_exact[mask] = pulse_value 

    return u_exact

# Load output files
files = sorted(glob.glob("output/*.csv"))
print(f"Found {len(files)} files")
if (len(files) == 0):
    raise RuntimeError("No output files found!")

# Subplot layout
nplots = len(files)
ncols = 3
nrows = math.ceil(nplots / ncols)

# Create figure
fig,axes = plt.subplots(nrows, ncols, figsize=(15, 4*nrows))

# Flatten axes array
axes = np.array(axes).flatten()

# Plot the snapshots
for i, filename in enumerate(files):
    # Load the numerical solution
    x,u = np.loadtxt(filename, delimiter=",", skiprows=1, unpack=True)

    # Physical time
    t = i * output_frequency * dt

    # Exact solution
    u_exact = exact_square_pulse(x, t, c)

    # Plot the numerical and exact solutions
    axes[i].plot(x, u, linewidth=2, label="Numerical")
    axes[i].step(x, u_exact, where="mid", linestyle="--", linewidth=2, label="Exact")

    # Format axes
    axes[i].set_xlim(0.0, 1.0)
    axes[i].set_ylim(-0.2, 1.2)
    axes[i].set_title(f"t = {t:.3f}")

    axes[i].grid(True)
    axes[i].legend()

# Hide unused subplots
for j in range(i+1, len(axes)):
    axes[j].axis("off")

fig.suptitle("1D linear advection: Square pulse", fontsize = 18)

plt.tight_layout()
plt.show()
