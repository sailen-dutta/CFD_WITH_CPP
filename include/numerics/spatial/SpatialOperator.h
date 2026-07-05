#pragma once
#include "core/Field1D.h"
class SpatialOperator {
    public:
        virtual ~SpatialOperator() = default;
        virtual void computeRHS(const Field1D& u, Field1D& rhs) const = 0;
};