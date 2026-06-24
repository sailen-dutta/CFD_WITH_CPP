#pragma once
#include "numerics/time/TimeIntegrator.h"

class SSPRK3 : public TimeIntegrator {
    public:
        void advance(Field1D& u, const FiniteVolumeOperator& op, double dt) const override;
};