#include "io/writers/VTKWriter1D.h"
#include <fstream>
#include <stdexcept>

void VTKWriter1D::write(const Field1D& field, const std::string& filename){
    std::ofstream out(filename);
    if (!out){
        throw std::runtime_error("Failed to open VTK file.");
    }

    const size_t npts = field.size();
    const std::size_t numVariables = field.numVariables();

    out << "# vtk DataFile Version 3.0\n";
    out << "1D CFD Solution.\n";
    out << "ASCII\n";
    out << "DATASET POLYDATA\n\n";

    out << "POINTS " << npts << " float\n";

    for (size_t i = 0; i < npts; ++i){
        out << field.grid().x(i) << " 0.0 0.0\n";
    }

    out << "\n";

    out << "LINES 1 " << (npts + 1) << "\n";
    out << npts;
    for (size_t i = 0; i < npts; ++i)
    {
        out << " " << i;
    }

    out << "\n\n";
    out << "POINT_DATA " << npts << "\n";
    /* Write one scalar field at a time */
    for (std::size_t k = 0; k < numVariables; ++k){
        out << "SCALARS U" << k << " float 1\n";
        out << "LOOKUP_TABLE default\n";

        /* Write the value of the k-th conserved variable
       at every grid point */
       for (std::size_t i = 0; i < npts; ++i){
            out << field[i][k] << "\n";    
       }
       out << "\n";
    }       
}

std::string VTKWriter1D::extension() const {
    return "vtk";
}