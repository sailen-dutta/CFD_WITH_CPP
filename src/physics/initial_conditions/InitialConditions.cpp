#include "physics/initial_conditions/InitialConditions.h"

/* Burgers' equation has a single conserved variable.
   Store the initial condition in the first (and only) component
   of the conserved variable vector. */
void InitialConditions::squarePulse(Field1D& field, double x_start, double x_end, double value){
    field.fill(0.0);
    for (size_t i = 0; i < field.size(); ++i){
        double x = field.grid().x(i);
        if (x >= x_start && x <= x_end){
            field[i][0] = value;
        }
    }
}

void InitialConditions::gaussian(Field1D& field, double center, double sigma){
    field.fill(0.0);
    for (size_t i = 0; i < field.size(); ++i){
        double x = field.grid().x(i);
        double exponent = -((x - center) * (x - center))/(2.0 * sigma * sigma);
        field[i][0] = std::exp(exponent);
    }
}

void InitialConditions::sinewave(Field1D& field){
    field.fill(0.0);
    constexpr double pi = std::numbers::pi;
    for (size_t i = 0; i < field.size(); ++i){
        double x = field.grid().x(i);
        field[i][0] = std::sin(4 * pi * x);
    }
}