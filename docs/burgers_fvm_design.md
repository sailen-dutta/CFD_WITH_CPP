# 1D Burgers Equation Solver Design

## Purpose

This document describes the architecture of the finite-volume Burgers equation solver. The primary goals of the design are:

* Separation of concerns
* Reusability of numerical components
* Extensibility for future PDEs
* Support for multiple numerical fluxes
* Support for multiple time integration schemes
* Clean application code with minimal conditional logic

The architecture follows the Method of Lines (MOL) approach, where spatial discretization and time integration are treated as independent components.

---

# Mathematical Background

## Burgers Equation

The inviscid Burgers equation is

$$
\frac{\partial u}{\partial t}+u\frac{\partial u}{\partial x} = 0
$$

For finite volume methods, it is preferable to write the equation in conservative form:

$$
\frac{\partial u}{\partial t} + \frac{\partial}{\partial x} \left( \frac{u^2}{2} \right) = 0
$$

The physical flux is therefore

$$
f(u) = \frac{u^2}{2}
$$

---

## Finite Volume Formulation

Integrating the conservation law over a control volume gives

$$
\frac{d}{dt} \int_{V_i} u dV + \oint_{\partial V_i} \mathbf{F} \cdot \mathbf{n} dS = 0
$$

For a one-dimensional uniform mesh this reduces to

$$
\frac{d u_i}{dt} = - \frac{F_{i+1/2} - F_{i-1/2}} {\Delta x}
$$

where

$$
F_{i+1/2}
$$

is the numerical flux at the interface between cells.

---

## Method of Lines

The finite volume discretization produces a system of ODEs:

$$
\frac{du}{dt} = R(u)
$$

where

$$
R(u) = - \frac{F_{i+1/2} - F_{i-1/2}} {\Delta x}
$$

The spatial discretization computes the residual (R(u)).

A separate time integrator advances the solution.

---

# High-Level Architecture

The solver is decomposed into independent components.

```text
Initial Condition
        |
        v
FluxFunction
        |
        v
NumericalFlux
        |
        v
FiniteVolumeOperator
        |
        v
TimeIntegrator
        |
        v
Updated Solution
```

Each component is responsible for exactly one aspect of the numerical method.

---

# Component Responsibilities

## FluxFunction

A FluxFunction represents the physical flux associated with a conservation law.

Interface:

```cpp
class FluxFunction
{
public:

    virtual ~FluxFunction() = default;

    virtual double flux(double u) const = 0;

    virtual double maxWaveSpeed(double u) const = 0;
};
```

Example implementations:

```text
BurgersFlux
LinearAdvectionFlux
```

For Burgers equation:

$$
f(u) = \frac{u^2}{2}
$$

and

$$
a(u) = |u|
$$

where (a(u)) is the characteristic wave speed.

The FluxFunction knows the physics of the PDE.

---

## NumericalFlux

A NumericalFlux computes a stable approximation of the interface flux.

Interface:

```cpp
class NumericalFlux
{
public:

    virtual ~NumericalFlux() = default;
    virtual double compute(double uL, double uR) const = 0;
};
```

Example implementations:

```text
RusanovFlux
GodunovFlux
CentralFlux
```

The NumericalFlux knows numerical methods but does not know the governing equation.

---

# Why NumericalFlux Stores a FluxFunction

The Rusanov flux requires:

* Physical flux values
* Characteristic wave speeds

These quantities depend on the PDE being solved.

For this reason:

```cpp
private:

    const FluxFunction& flux_;
```

is stored inside the numerical flux.

Example:

```cpp
BurgersFlux burgers;

RusanovFlux flux(burgers);
```

The Rusanov implementation can now evaluate:

```cpp
flux_.flux(u)
```

and

```cpp
flux_.maxWaveSpeed(u)
```

without knowing whether the PDE is:

* Burgers equation
* Linear advection
* Euler equations

This promotes reuse.

---

# Rusanov Flux

The Rusanov flux is defined as

$$
F = \frac12 \left( f(u_L) + f(u_R) \right) - \frac12 a \left(u_R-u_L\right)
$$

where

$$
a = \max\left(|u_L|,|u_R|\right)
$$

for Burgers equation.

The first term represents a central average.

The second term introduces numerical dissipation that stabilizes discontinuities.

---

## FiniteVolumeOperator

The FiniteVolumeOperator computes the spatial residual.

Interface:

```cpp
class FiniteVolumeOperator
{
public:

    virtual ~FiniteVolumeOperator() = default;

    virtual void computeRHS(const Field1D& u,Field1D& rhs) const = 0;
};
```

Example implementation:

```text
FirstOrderFVOperator
```

The operator computes

$$
R(u) = - \frac{F_{i+1/2} - F_{i-1/2}} {\Delta x}
$$

and stores the result in rhs.

No time integration is performed here.

---

# Why FiniteVolumeOperator Stores a NumericalFlux

The spatial operator must evaluate interface fluxes.

It therefore depends on a NumericalFlux.

```cpp
private:

    const NumericalFlux& flux_;
```

Example:

```cpp
RusanovFlux numerical_flux(burgers);

FirstOrderFVOperator spatial(numerical_flux);
```

The spatial operator does not know:

* How Rusanov works
* How Godunov works
* How HLL works

It simply requests:

```cpp
flux_.compute(...)
```

This makes the spatial operator independent of the chosen numerical flux.

---

## TimeIntegrator

The TimeIntegrator advances the solution in time.

Interface:

```cpp
class TimeIntegrator
{
public:

    virtual ~TimeIntegrator() = default;

    virtual void advance(Field1D& u, const FiniteVolumeOperator& op, double dt) const = 0;
};
```

Example implementations:

```text
ForwardEuler
RK2
RK4
```

The TimeIntegrator knows nothing about:

* Burgers equation
* Flux functions
* Numerical fluxes
* Boundary conditions

It only advances an ODE system.

---

# Why TimeIntegrator Uses a FiniteVolumeOperator

The time integrator requires the residual

$$
R(u)
$$

but should not know how it is computed.

For this reason:

```cpp
const FiniteVolumeOperator& op
```

is passed to the integrator.

Example:

```cpp
integrator.advance(u, spatial, dt);
```

The integrator simply asks:

```cpp
op.computeRHS(...)
```

and uses the resulting residual.

This allows the same RK2 implementation to work with any spatial discretization.

---

# Runtime Polymorphism

The framework relies heavily on runtime polymorphism.

Example:

```cpp
BurgersFlux burgers;

RusanovFlux flux(burgers);
```

The member

```cpp
const FluxFunction& flux_;
```

stores a reference to the base class.

When

```cpp
flux_.flux(u)
```

is called, C++ performs virtual dispatch and invokes

```cpp
BurgersFlux::flux(u)
```

because the underlying object is a BurgersFlux.

The same mechanism is used throughout the architecture.

---

# CFL Condition

For Burgers equation, the characteristic speed is

$$
a(u) = u
$$

The timestep is therefore

$$
\Delta t = CFL\frac{\Delta x}{\max |u|}
$$

The maximum wave speed changes during the simulation and must be recomputed every timestep.

---

# Boundary Conditions

The initial implementation assumes periodic boundaries.

$$
u_{-1} = u_{N-1}
$$

and

$$
u_N = u_0
$$

Future work should introduce:

```text
BoundaryCondition
    |
    +-- PeriodicBC
    +-- DirichletBC
    +-- NeumannBC
```

This removes boundary-specific logic from the numerical schemes.

---

# Factory Pattern

## Motivation

Without factories, the application becomes cluttered with object creation logic.

Example:

```cpp
if (flux_name == "rusanov") {
    ...
}

if (integrator_name == "rk2") {
    ...
}
```

As more numerical methods are added, the application becomes difficult to maintain.

Factories centralize object creation.

---

## Flux Function Factory

```cpp
class FluxFunctionFactory
{
public:

    static std::unique_ptr<FluxFunction> create(const std::string& name);
};
```

Example:

```cpp
auto flux_function = FluxFunctionFactory::create("burgers");
```

---

## Numerical Flux Factory

```cpp
class NumericalFluxFactory
{
public:

    static std::unique_ptr<NumericalFlux> create(const std::string& name,const FluxFunction& flux);
};
```

Example:

```cpp
auto numerical_flux = NumericalFluxFactory::create("rusanov", *flux_function);
```

---

## Time Integrator Factory

```cpp
class TimeIntegratorFactory
{
public:

    static std::unique_ptr<TimeIntegrator>create(const std::string& name);
};
```

Example:

```cpp
auto integrator = TimeIntegratorFactory::create("rk2");
```

---

# Benefits of Factories

Factories provide several advantages:

* Centralized object creation
* Cleaner application code
* Easier extension of numerical methods
* Reduced conditional logic
* Better separation of responsibilities

The application should configure the simulation, not construct numerical algorithms.

---

# Example Simulation Setup

With factories, the application becomes concise:

```cpp
auto flux_function = FluxFunctionFactory::create("burgers");

auto numerical_flux = NumericalFluxFactory::create("rusanov", *flux_function);

auto spatial = std::make_unique<FirstOrderFVOperator>(*numerical_flux);

auto integrator = TimeIntegratorFactory::create("rk2");
```

The numerical details are hidden behind abstractions.

---

# Future Extensions

The current architecture can be extended with minimal modification.

Possible additions include:

```text
RK2
RK4
SSPRK3

GodunovFlux
HLLFlux
RoeFlux

LinearAdvectionFlux

Euler Equations

Sod Shock Tube

2D Finite Volume Methods
```

Most new functionality can be introduced by creating new derived classes rather than modifying existing code.

---

# Design Principles

1. Each class should have a single responsibility.

2. Spatial discretization and time integration should remain independent.

3. Numerical methods should be reusable across multiple PDEs.

4. Construction logic should be isolated in factories.

5. The application layer should orchestrate components rather than implement algorithms.

6. Dependencies should be expressed through abstract interfaces rather than concrete classes.

Following these principles results in a modular, extensible, and maintainable CFD framework.
