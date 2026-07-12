#include "physics/BurgersEquation.h"
#include <cmath>

double BurgersEquation::flux(double u) const {
    return 0.5 * u * u;
}

double BurgersEquation::maxWaveSpeed(double u) const {
    return std::abs(u);
}