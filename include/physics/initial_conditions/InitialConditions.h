#pragma once
#include "core/Field1D.h"
#include <numbers>
#include <cmath>

namespace InitialConditions{

    void squarePulse(Field1D& field, double x_start, double x_end, double value);

    void gaussian(Field1D& field, double center, double sigma);

    void sinewave(Field1D& field);

    void sodShockTube(Field1D& field, double x_discontinuity = 0.5, double gamma = 1.4);
}
