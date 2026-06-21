#include "io/OutputWriterFactory.h"
#include "io/CSVWriter.h"
#include "io/VTKWriter1D.h"
#include "io/TecplotWriter1D.h"

#include <stdexcept>

std::unique_ptr<OutputWriter> OutputWriterFactory::create(const std::string& format){
    if (format == "vtk"){
        return std::make_unique<VTKWriter1D>();
    }
    else if (format == "tecplot"){
        return std::make_unique<TecplotWriter1D>();
    }
    else if (format == "csv"){
        return std::make_unique<CSVWriter>();
    }
    else{
        throw std::runtime_error("Unknown output format " + format);
    }    
}