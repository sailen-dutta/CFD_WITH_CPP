#include "io/TecplotWriter1D.h"
#include <fstream>
#include <stdexcept>

void TecplotWriter1D::write(const Field1D& field, const std::string& filename){
    std::ofstream out(filename);
    if (!out){
        throw std::runtime_error("Cannot open Tecplot file.");
    }

    out << "TITLE = \"1D CFD Solution\"\n";

    out << "VARIABLES = \"x\", \"u\"\n";

    out << "ZONE I=" << field.size() << ", F=POINT\n";

    for (size_t i = 0; i < field.size(); ++i){
        out << field.grid().x(i) << " " << field[i] << "\n";
    }
}

std::string TecplotWriter1D::extension() const {
    return "dat";
}