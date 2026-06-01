#pragma once
#include "core/Field1D.h"

namespace ErrorAnalysis {
    double computeL2Error(const Field1D& numerical, const Field1D& exact);
    double computeLinfError(const Field1D& numerical, const Field1D& exact);
}