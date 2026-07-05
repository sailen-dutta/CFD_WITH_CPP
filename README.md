# CFD_WITH_CPP

An ongoing open-source Computational Fluid Dynamics (CFD) project written in modern C++.

This project is developed from scratch as a learning platform to strengthen my understanding of:

- numerical methods for CFD
- finite-volume methods
- modern C++ software design
- scientific computing architecture
- high-performance computing concepts

The objective is not only to implement CFD algorithms, but also to design a clean, extensible solver framework similar in philosophy to larger scientific codes.

---

## Motivation

I come from a background in Computational Fluid Dynamics and numerical methods.

This repository is a long-term personal project to combine CFD theory with practical software engineering.  
Every major component is implemented manually to better understand the underlying algorithms instead of relying on existing CFD libraries.

Key learning goals:

- Implement CFD methods from first principles
- Develop maintainable modern C++ code
- Learn object-oriented design for scientific applications
- Build reusable solver infrastructure
- Practice testing and validation workflows
- Explore performance optimization and HPC techniques

---

# Current Features

## Core Infrastructure

- Custom dynamic `Vector` class
- Structured 1D mesh (`Grid1D`)
- Scalar solution field abstraction (`Field1D`)
- Modular CMake build system
- Unit testing using Google Test
- JSON-driven runtime configuration

---

# Numerical Methods

## Governing Equations

Currently supported:

- 1D Linear Advection Equation
- 1D Inviscid Burgers Equation

---

## Spatial Discretization

Finite Volume Method (FVM) framework:

- Conservative finite-volume formulation
- Numerical flux abstraction
- Reconstruction-based interface calculation

Implemented flux methods:

- Rusanov / Local Lax-Friedrichs flux

Implemented reconstruction schemes:

- Piecewise constant reconstruction (first-order)
- MUSCL reconstruction (second-order)
- Minmod slope limiter

Planned:

- Higher-order limiters
- WENO reconstruction
- Additional approximate Riemann solvers

---

## Time Integration

Runtime-selectable time integration framework:

Implemented:

- Forward Euler
- Second-order Runge-Kutta (RK2)
- SSPRK3 (Strong Stability Preserving Runge-Kutta)

Planned:

- Classical RK4
- Implicit schemes
- Dual-time stepping experiments

---

# Software Architecture

The solver uses modular C++ design concepts:

- Abstract interfaces
- Runtime polymorphism
- Factory pattern
- Function pointer based registries
- Dependency injection between solver components

Current factories:

- Time Integrator Factory
- Output Writer Factory
- Initial Condition Factory

Planned:

- Reconstruction Factory
- Flux Factory
- Boundary Condition Factory

---

# Input Configuration

Simulations are controlled using JSON files.

Example:

```json
{
    "physics": {
        "equation": "burgers"
    },

    "numerics": {
        "flux": "rusanov",
        "reconstruction": "muscl",
        "time_integrator": "ssprk3"
    },

    "initial_condition": {
        "type": "gaussian"
    }
}
```

This allows changing numerical methods without recompilation.

---

# Output Support

Supported output formats:

- CSV
- Tecplot ASCII
- VTK

Additional run information:

- Simulation metadata
- Numerical configuration summary
- Regression comparison support

---

# Python Utilities

Python scripts are used for:

- Solution visualization
- Comparing numerical schemes
- Regression checks
- Error analysis

Libraries:

- NumPy
- Pandas
- Matplotlib

---

# Testing

The project uses Google Test.

Current tests cover:

- Vector operations
- Grid generation
- Field operations
- Error analysis utilities
- Numerical components

Run tests:

```bash
ctest --output-on-failure
```

---

# Build Instructions

Configure:

```bash
mkdir build
cd build
cmake -G Ninja ..
```

Build:

```bash
cmake --build .
```

Run:

```bash
./burgers1d
```

---

# Project Structure

```text
CFD_WITH_CPP/

include/
    core/              Core data structures
    numerics/          Numerical methods
    physics/           Physics models and initial conditions
    io/                Input/output infrastructure

src/
    core/
    numerics/
    physics/
    io/

apps/
    Solver applications

tests/
    Google Test unit tests

python/
    Visualization and analysis tools

config/
    JSON simulation files
```

---

# Future Development Roadmap

## Numerical Methods

- Additional reconstruction schemes
- Advanced slope limiters
- WENO schemes
- Euler equations
- Shock tube problems
- 2D finite-volume solver
- Navier-Stokes equations

---

## Software Engineering

- Improved solver driver architecture
- Generic factory framework
- More extensive unit testing
- Continuous integration

---

## High Performance Computing

Planned experiments:

- OpenMP shared-memory parallelism
- MPI domain decomposition
- SLURM-based workflows
- GPU acceleration exploration

---

# Long-Term Vision

The long-term goal is to evolve this repository into a small but well-structured CFD research framework.

The emphasis is on:

- correctness
- clean architecture
- numerical understanding
- maintainability

Performance optimizations are introduced gradually after establishing a reliable numerical foundation.