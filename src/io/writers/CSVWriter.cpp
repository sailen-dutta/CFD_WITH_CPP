#include "io/writers/CSVWriter.h"
#include <fstream>
#include <stdexcept>
#include <iomanip>

void CSVWriter::write(const Field1D& field, const std::string& filename){
    std::ofstream out(filename);
    const std::size_t numVariables = field.numVariables();

    if(!out){
        throw std::runtime_error("Failed to open output file!" + filename);
    }

    out << std::setprecision(16);

    /* Header 
       x,U0,U1,U2 etc.
    */
    out << "x";

    for (std::size_t i = 0; i < numVariables; ++i){
        out << ",U" << i;
    }
    out << "\n";

    /* The values after the header */
    for (std::size_t i = 0; i < field.size(); ++i){
        out << field.grid().x(i);
        for (std::size_t k = 0; k < numVariables; ++k){
            out << "," << field[i][k];
        }
        out << "\n";
    }  
}

std::string CSVWriter::extension() const {
    return "csv";
}