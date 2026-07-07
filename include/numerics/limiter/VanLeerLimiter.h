#pragma once
#include "numerics/limiter/SlopeLimiter.h"

class VanLeerLimiter : public SlopeLimiter {
    public:
        double limit(double left, double right) const override;
};