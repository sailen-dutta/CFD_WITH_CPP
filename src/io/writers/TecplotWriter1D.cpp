#include "io/writers/TecplotWriter1D.h"
#include <fstream>
#include <stdexcept>

void TecplotWriter1D::write(const Field1D& field, const std::string& filename){
    std::ofstream out(filename);

    /* Number of conserved variables stored in each computational cell.
       Examples:
           Burgers : 1 (u)
           Euler   : 3 (rho, rho*u, E)
    */
    const std::size_t numVariables = field.numVariables();

    if (!out){
        throw std::runtime_error("Cannot open Tecplot file.");
    }

    /* Tecplot title displayed in the visualization window */
    out << "TITLE = \"1D CFD Solution\"\n";
    
    /* Declare the variables present in the file.
       The output is generated dynamically so that the same writer works
       for scalar equations (Burgers) as well as systems (Euler, etc.). */
    out << "VARIABLES = \"x\"";
    for (std::size_t i = 0; i < numVariables; ++i){
        out << ", \"U" << i << "\"" ;
    }
    out << "\n";

    /* A single structured 1D zone with one point per computational cell */
    out << "ZONE I=" << field.size() << ", F=POINT\n";

    /* Write one row per computational cell:
           x-coordinate   U0   U1   U2 ...
    */
    for (size_t i = 0; i < field.size(); ++i){
        /* Physical location of the cell centre */
        out << field.grid().x(i);

        /* Write all conserved variables stored in this cell
        i         : cell index
        field[i]  : Vector of conserved variables in cell i
        k         : conserved variable index
        field[i][k]: k-th conserved variable in cell i*/
        for (std::size_t k = 0; k < numVariables; ++k){
            out << " " << field[i][k];
        }
        out << "\n";
    }
}

std::string TecplotWriter1D::extension() const {
    return "dat";
}