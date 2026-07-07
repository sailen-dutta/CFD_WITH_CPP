#include "numerics/limiter/SlopeLimiter.h"

class MinmodLimiter : public SlopeLimiter {
    public:
        double limit(double left, double right) const override;
};