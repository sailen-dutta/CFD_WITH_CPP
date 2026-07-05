#pragma once
#include "numerics/time/TimeIntegrator.h"

class RK2 : public TimeIntegrator {
    public:
        void advance(Field1D& u, const SpatialOperator& op, double dt) const override;
};
