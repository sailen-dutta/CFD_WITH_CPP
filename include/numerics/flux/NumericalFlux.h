#pragma once

class NumericalFlux{
    public:
        virtual ~NumericalFlux() = default;
        virtual double compute(double uL, double uR) const = 0;
};