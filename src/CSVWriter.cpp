#include "CSVWriter.h"
#include <fstream>
#include <stdexcept>

void CSVWriter::write(const Field1D& field, const std::string& filename){
    std::ofstream out(filename);

    if(!out){
        throw std::runtime_error("Failed to open output file!");
    }

    out << "x,u\n";

    for (size_t i = 0; i < field.size(); ++i){
        out << field.grid().x(i) << "," << field[i] << "\n";
    }    
}