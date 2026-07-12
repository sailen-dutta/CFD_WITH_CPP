#pragma once

#include "numerics/flux/NumericalFlux.h"

class RusanovFlux : public NumericalFlux {
    public:
        RusanovFlux() = default;
        double compute(double uL, double uR, const HyperbolicEquation& equation) const override;   
};