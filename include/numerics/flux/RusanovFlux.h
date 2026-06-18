#pragma once

#include "numerics/flux/NumericalFlux.h"
#include "physics/FluxFunction.h"

class RusanovFlux : public NumericalFlux {
    public:
        explicit RusanovFlux(const FluxFunction& flux);
        double compute(double uL, double uR) const override;

    private:
        const FluxFunction& flux_;
};