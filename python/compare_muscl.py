import os
import pandas as pd
import matplotlib.pyplot as plt

def read_tecplot(filename):
    """
    Reads a simple Tecplot data file containing x and u columns
    """
    x = []
    u = []

    with open(filename) as f:
        reading = False

        for line in f:
            line = line.strip()

            if not reading:
                if line.startswith("ZONE"):
                    reading = True
                continue

            if line == "":
                continue

            values = line.split()

            x.append(float(values[0]))
            u.append(float(values[1]))

    return pd.DataFrame({"x" : x, "u" : u})

# Directory containing results
base_dir = "output/burgers"

# Folder name : legend
cases = {
        "rusanov_piecewise_constant_ssprk3" : "Piecewise Constant",        
        "rusanov_muscl_unlimited_ssprk3"    : "Unlimited",
        "rusanov_muscl_minmod_ssprk3"       : "MinMod",
        "rusanov_muscl_vanleer_ssprk3"      : "Van Leer",
        "rusanov_muscl_superbee_ssprk3"     : "Superbee",
        }

plt.figure(figsize = (12,6))

for folder,label in cases.items():
    filename = os.path.join(base_dir,folder,"final.dat")

    if not os.path.exists(filename):
        print(f"Skipping file: {filename}")
        continue

    df = read_tecplot(filename)
    
    plt.plot(df["x"],df["u"], linewidth = 2, label = label)


plt.xlabel("x")
plt.ylabel("u")
plt.title("Burgers equation : MUSCL Reconstruction Comparison")
plt.grid(True)
plt.legend()
plt.tight_layout()
plt.show()

