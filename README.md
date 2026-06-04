# CFD with C++

A long-term learning project focused on implementing Computational Fluid Dynamics (CFD) solvers in modern C++.

## Motivation

I come from a background in Computational Fluid Dynamics (CFD) and numerical methods.  
This repository is my attempt to deepen my software engineering and modern C++ skills by building CFD solvers from scratch.

The primary goals are:

- Learn modern C++
- Learn software architecture for scientific computing
- Learn CMake and build systems
- Learn unit testing with Google Test
- Implement numerical schemes from first principles
- Build reusable CFD infrastructure
- Eventually develop a Qt-based GUI
- Visualize results using Python

---

## Current Features

- Custom `Vector` class
- `Grid1D` structured mesh
- `Field1D` scalar field abstraction
- Google Test unit tests
- CMake-based modular build system
- CSV output for visualization
- Python plotting pipeline

---

## Planned Features

### 1D Solvers
- Linear advection equation
- Diffusion equation
- Burgers equation
- Shock tube problems

### Numerical Schemes
- Upwind
- FTCS
- Lax-Friedrichs
- Lax-Wendroff
- MacCormack

### Infrastructure
- Boundary condition framework
- Time integrators
- File I/O improvements
- Configuration parsing

### Future Goals
- 2D solvers
- Navier-Stokes equations
- Qt GUI
- Parallelization experiments
- Performance profiling

---

## Technologies Used

- C++17
- CMake
- Google Test
- Python (NumPy + Matplotlib)

Planned:
- Qt
- Eigen or custom linear algebra
- MPI (future)

---

## Project Structure

```text
include/    -> Header files
src/        -> Implementations
tests/      -> Unit tests
apps/       -> Solver executables
python/     -> Visualization scripts
```

---

## Build Instructions

```bash
mkdir build
cd build

cmake -G "MinGW Makefiles" .. (or cmake -G Ninja ..)
cmake --build .
```

Run tests:

```bash
ctest --output-on-failure
```

---

## Visualization

Python scripts inside `python/` can be used to visualize solver output.

---

## Learning Philosophy

The emphasis of this repository is clarity, correctness, and learning — not production-grade performance.

Many components are intentionally implemented manually (instead of using existing libraries) to better understand:

- numerical methods,
- memory management,
- data structures,
- software design,
- and scientific computing workflows.