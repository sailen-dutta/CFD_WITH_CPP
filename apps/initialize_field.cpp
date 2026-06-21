#include "io/CSVWriter.h"
#include "core/Field1D.h"
#include "core/Grid1D.h"
#include "physics/initial_conditions/InitialConditions.h"

int main(){
    Grid1D grid(0.0, 1.0, 101);
    Field1D u(grid);

    u.fill(0.0);

    InitialConditions::squarePulse(u, 0.4, 0.6, 1.0);

    CSVWriter writer;
    writer.write(u, "solution.csv");

    return 0;
}