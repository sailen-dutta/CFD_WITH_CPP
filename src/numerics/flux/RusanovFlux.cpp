#include "numerics/flux/RusanovFlux.h"
#include <algorithm>

Vector RusanovFlux::compute(const Vector& UL, const Vector& UR, const HyperbolicEquation& equation) const {
    const Vector FL = equation.flux(UL);
    const Vector FR = equation.flux(UR);

    const double a = std::max(equation.maxWaveSpeed(UL), equation.maxWaveSpeed(UR));

    return 0.5 * (FL + FR) - 0.5 * a * (UR - UL);
}

