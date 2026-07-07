#include "numerics/limiter/SuperbeeLimiter.h"
#include <algorithm>
#include <cmath>

double SuperbeeLimiter::limit(double left, double right) const {
    if (left * right <= 0.0) return 0.0;

    double s = (left > 0.0) ? 1.0 : -1.0;

    double a = std::min(2 * std::abs(left), std::abs(right));

    double b = std::min(std::abs(left), 2 * std::abs(right));

    return s * std::max(a,b);
}