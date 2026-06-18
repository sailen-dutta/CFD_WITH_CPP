#pragma once
#include "numerics/time/TimeIntegrator.h"

class ForwardEuler : public TimeIntegrator {
    public:
        void advance(Field1D& u, const FiniteVolumeOperator& op, double dt) const override;
};