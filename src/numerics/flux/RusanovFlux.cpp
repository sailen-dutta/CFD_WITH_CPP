#pragma once

#include "numerics/flux/RusanovFlux.h"
#include <algorithm>

RusanovFlux::RusanovFlux(const FluxFunction& flux): flux_(flux) {}

double RusanovFlux::compute(double uL, double uR) const {
    const double fL = flux_.flux(uL);
    const double fR = flux_.flux(uR);

    const double a = std::max(flux_.maxWaveSpeed(uL), flux_.maxWaveSpeed(uR));

    return 0.5 * (fL + fR) - 0.5 * a * (uR - uL);
}

