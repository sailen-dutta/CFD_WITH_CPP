#pragma once
#include "physics/HyperbolicEquation.h"

class NumericalFlux{
    public:
        virtual ~NumericalFlux() = default;
        virtual double compute(double uL, double uR, const HyperbolicEquation& equation) const = 0;
};