#include "physics/ExactSolutions.h"
#include <cmath>

namespace ExactSolutions {
    void sineWave(Field1D& u_exact, double c, double t){
        constexpr double pi = std::numbers::pi;
        for (size_t i = 0; i < u_exact.size(); i++){
            double x = u_exact.grid().x(i);
            u_exact[i] = std::sin(4 * pi * (x - c * t));
        }
    }
}