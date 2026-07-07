#include "numerics/limiter/NoLimiter.h"

double NoLimiter::limit(double, double) const {
    return 0.0;
}