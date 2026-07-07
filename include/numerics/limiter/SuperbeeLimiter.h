#pragma once
#include "numerics/limiter/SlopeLimiter.h"

class SuperbeeLimiter : public SlopeLimiter {
    public:
        double limit(double left, double right) const override;
};