#pragma once
#include "physics/FluxFunction.h"
#include <cmath>

class BurgersFlux : public FluxFunction {
    public:
        double flux(double u) const override {
            return 0.5 * u * u;
        }

        double maxWaveSpeed(double u) const override {
            return std::abs(u);
        }
};