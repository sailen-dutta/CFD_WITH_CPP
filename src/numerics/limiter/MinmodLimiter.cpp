#include "numerics/limiter/MinmodLimiter.h"
#include <algorithm>
#include <cmath>

double MinmodLimiter::limit(double left, double right) const {
    if (left * right <= 0.0) return 0.0;

    return std::copysign(std::min(std::abs(left), std::abs(right)), left);
}