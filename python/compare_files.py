import numpy as np
import pandas as pd
import os
from pathlib import Path 

# Root directories containing the base version and new version
OLD_BASE = Path("comparison/burgers_sinewave_old")
NEW_BASE = Path("comparison/burgers_sinewave_new")

# List of limiters
LIMITERS = ["unlimited", "minmod", "vanleer", "superbee"]

def read_tecplot(filename):
    """
    Reads a simple Tecplot ASCII file containing x and u columns
    """
    x=[]
    u=[]
    
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

    return pd.DataFrame({
        "x" : x,
        "u" : u
    })

def compare_case(case_name):
    old = read_tecplot(OLD_BASE / case_name / "final.dat")
    new = read_tecplot(NEW_BASE / case_name / "final.dat")
    grid_error = np.max(np.abs(old["x"] - new["x"]))
    difference = np.abs(old["u"] - new["u"])
    linf_error = difference.max()
    l2_error = np.sqrt(np.mean(difference ** 2))
    passed = linf_error < 1e-14

    print(f"\nCase: {case_name}")
    print("-" * 50)
    print(f"Cells           : {len(old)}")
    print(f"Grid difference : {grid_error:.16e}")
    print(f"L_inf error     : {linf_error:.16e}")
    print(f"L2 error        : {l2_error:.16e}")
    print("Status          :", "PASS" if passed else "FAIL")

    return passed

def main():
    all_passed = True

    for limiter in LIMITERS:
        case = f"rusanov_muscl_{limiter}_ssprk3"

        if not compare_case(case):
            all_passed = False

    print("\n" + "=" * 50)

    if all_passed:
        print("ALL REGRESSION TESTS PASSED")
    else:
        print("SOME REGRESSION TESTS FAILED")

    print("=" * 50)

if __name__ == "__main__":
    main()