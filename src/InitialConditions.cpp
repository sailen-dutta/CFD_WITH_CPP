#include "InitialConditions.h"

void InitialConditions::squarePulse(Field1D& field, double x_start, double x_end, double value){
    for (size_t i = 0; i < field.size(); ++i){
        double x = field.grid().x(i);
        if (x >= x_start && x <= x_end){
            field[i] = value;
        }
    }
}