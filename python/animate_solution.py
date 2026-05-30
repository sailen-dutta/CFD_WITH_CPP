import glob
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation

# Get all output files
files = sorted(glob.glob("output/*.csv"))
print(files)
print(len(files))

# Figure setup
fig, ax = plt.subplots()
line, = ax.plot([],[])
ax.set_xlim(0.0, 1.0)
ax.set_ylim(-0.1, 1.1)
ax.set_xlabel("x")
ax.set_ylabel("u")
ax.grid(True)

# Function to update animation
def update(frame):
    x,u = np.loadtxt(files[frame], delimiter=",", skiprows=1, unpack=True)
    line.set_data(x,u)
    time = frame * 10 * 0.005
    ax.set_title(f"t = {time:.3f}")
    return line,

# Create animation
ani = animation.FuncAnimation(fig, update, frames=len(files), interval=200, blit=False)

plt.show()