#pragma once
#include "physics/equations/HyperbolicEquation.h"
#include "core/Vector.h"

class NumericalFlux{
    public:
        virtual ~NumericalFlux() = default;
        virtual Vector compute(const Vector& UL, const Vector& UR, const HyperbolicEquation& equation) const = 0;
};