#include "numerics/flux/RusanovFlux.h"
#include <algorithm>

double RusanovFlux::compute(double uL, double uR, const HyperbolicEquation& equation) const {
    const double fL = equation.flux(uL);
    const double fR = equation.flux(uR);

    const double a = std::max(equation.maxWaveSpeed(uL), equation.maxWaveSpeed(uR));

    return 0.5 * (fL + fR) - 0.5 * a * (uR - uL);
}

