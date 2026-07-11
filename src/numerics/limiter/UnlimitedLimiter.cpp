#include "numerics/limiter/UnlimitedLimiter.h"

double UnlimitedLimiter::limit(double left , double right) const {
    return 0.5 * (left + right);    /* left = u[i] - u[i-1], right = u[i+1] - u[i]*/
}