#include "CSVWriter.h"
#include "Field1D.h"
#include "Grid1D.h"
#include "InitialConditions.h"

int main(){
    Grid1D grid(0.0, 1.0, 101);
    Field1D u(grid);

    u.fill(0.0);

    InitialConditions::squarePulse(u, 0.4, 0.6, 1.0);

    CSVWriter::write(u, "solution.csv");

    return 0;
}