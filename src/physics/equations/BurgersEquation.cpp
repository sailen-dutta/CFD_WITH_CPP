#include "physics/equations/BurgersEquation.h"
#include <cmath>

Vector BurgersEquation::flux(const Vector& U) const {
    Vector F(numVariables());
    const double u = U[0];
    F[0] = 0.5 * u * u;
    return F;
}

double BurgersEquation::maxWaveSpeed(const Vector& U) const {
    return std::abs(U[0]);
}