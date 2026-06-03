#pragma once
#include "core/Field1D.h"

namespace ExactSolutions{
    void sineWave(Field1D& u_exact, double c, double t);

    void squarePulse(Field1D& u_exact, double c, double t, double pulse_start, double pulse_end, double value);
}