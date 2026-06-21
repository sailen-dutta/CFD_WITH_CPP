#include "physics/initial_conditions/InitialConditions.h"


void InitialConditions::squarePulse(Field1D& field, double x_start, double x_end, double value){
    for (size_t i = 0; i < field.size(); ++i){
        double x = field.grid().x(i);
        if (x >= x_start && x <= x_end){
            field[i] = value;
        }
    }
}

void InitialConditions::gaussian(Field1D& field, double center, double sigma){
    for (size_t i = 0; i < field.size(); ++i){
        double x = field.grid().x(i);
        double exponent = -((x - center) * (x - center))/(2.0 * sigma * sigma);
        field[i] = std::exp(exponent);
    }
}

void InitialConditions::sinewave(Field1D& field){
    constexpr double pi = std::numbers::pi;
    for (size_t i = 0; i < field.size(); ++i){
        double x = field.grid().x(i);
        field[i] = std::sin(4 * pi * x);
    }
}