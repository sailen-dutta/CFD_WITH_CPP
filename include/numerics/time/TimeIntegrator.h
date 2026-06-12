#pragma once

#include "core/Field1D.h"
#include "numerics/spatial/FiniteVolumeOperator.h"

class TimeIntegrator {
    public:
        virtual ~TimeIntegrator() = default;
        virtual void advance(Field1D& u, const FiniteVolumeOperator& op, double dt) const = 0;
};