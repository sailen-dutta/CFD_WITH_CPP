#pragma once

#include "numerics/flux/NumericalFlux.h"

class RusanovFlux : public NumericalFlux {
    public:
        RusanovFlux() = default;
        Vector compute(const Vector& UL, const Vector& UR, const HyperbolicEquation& equation) const override;   
};