#pragma once
#include "numerics/limiter/SlopeLimiter.h"

/* Unlimited central slope reconstruction 
   Provides second order MUSCL reconstruction without monotonicity constraints */
class UnlimitedLimiter : public SlopeLimiter {
    public:
        double limit(double left, double right) const override;
};