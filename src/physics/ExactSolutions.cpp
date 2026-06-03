#include "physics/ExactSolutions.h"
#include <cmath>
#include <numbers>

namespace ExactSolutions {
    void sineWave(Field1D& u_exact, double c, double t){
        constexpr double pi = std::numbers::pi;
        for (size_t i = 0; i < u_exact.size(); i++){
            double x = u_exact.grid().x(i);
            u_exact[i] = std::sin(4 * pi * (x - c * t));
        }
    }

    void squarePulse(Field1D& u_exact, double c, double t, double pulse_start, double pulse_end, double value){
        u_exact.fill(0.0);
        for (size_t i = 0; i < u_exact.size(); ++i){
            double x = u_exact.grid().x(i);

            /* Shift coordinates backward */
            double x_shift = x - c * t;

            /* Periodic wrap */
            while (x_shift < 0.0){
                x_shift += 1.0;
            }

            while (x_shift > 1.0){
                x_shift -= 1.0;
            }

            /* Inside pulse? */
            if (x_shift >= pulse_start && x_shift <= pulse_end){
                u_exact[i] = value;
            }
        }
    }
}