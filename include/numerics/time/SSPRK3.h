#pragma once
#include "numerics/time/TimeIntegrator.h"

class SSPRK3 : public TimeIntegrator {
    public:
        void advance(Field1D& u, const SpatialOperator& op, double dt) const override;
};