#include "numerics/limiter/VanLeerLimiter.h"

double VanLeerLimiter::limit(double left, double right) const {
    if (left * right <= 0.0) return 0.0;

    return (2.0 * left * right) / (left + right);
}