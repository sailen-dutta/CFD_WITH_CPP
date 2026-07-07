#pragma once
#include "numerics/limiter/SlopeLimiter.h"

class NoLimiter : public SlopeLimiter {
    public:
        double limit(double left, double right) const override;
};