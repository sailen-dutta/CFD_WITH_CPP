#include "io/CSVWriter.h"
#include <fstream>
#include <stdexcept>
#include <iomanip>

void CSVWriter::write(const Field1D& field, const std::string& filename){
    std::ofstream out(filename);

    if(!out){
        throw std::runtime_error("Failed to open output file!" + filename);
    }

    out << std::setprecision(16);

    out << "x,u\n";

    for (size_t i = 0; i < field.size(); ++i){
        out << field.grid().x(i) << "," << field[i] << "\n";
    }    
}