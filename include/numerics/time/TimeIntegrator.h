#pragma once

#include "core/Field1D.h"
#include "numerics/spatial/SpatialOperator.h"

class TimeIntegrator {
    public:
        virtual ~TimeIntegrator() = default;
        virtual void advance(Field1D& u, const SpatialOperator& op, double dt) const = 0;
};