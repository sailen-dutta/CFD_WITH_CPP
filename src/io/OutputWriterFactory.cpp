#include "io/OutputWriterFactory.h"
#include "io/CSVWriter.h"
#include "io/VTKWriter1D.h"
#include "io/TecplotWriter1D.h"

#include <stdexcept>
#include <memory>
#include <unordered_map>

namespace{
    /* -------------
    Creator functions:
    Each function creates a concrete OutputWriter object.
    These functions all have the same signature, allowing them to be stored in a 
    lookup table using function pointers.
     --------------- */
    std::unique_ptr<OutputWriter> createCSV() {
        return std::make_unique<CSVWriter>();
    }

    std::unique_ptr<OutputWriter> createTecplot() {
        return std::make_unique<TecplotWriter1D>();
    }

    std::unique_ptr<OutputWriter> createVTK() {
        return std::make_unique<VTKWriter1D>();
    }

    /* Function pointer type */
    using Creator = std::unique_ptr<OutputWriter> (*)();

    /* A registry mapping output format names to their corresponding creator functions.*/
    std::unordered_map<std::string, Creator> lookup_table = {
        {"csv",     createCSV},
        {"tecplot", createTecplot},
        {"vtk",     createVTK}
    };
}

std::unique_ptr<OutputWriter> OutputWriterFactory::create(const std::string& file_format){
  /* Lookup the requested file format */
  auto it = lookup_table.find(file_format);
  
  if ( it == lookup_table.end()){
    throw std::runtime_error("Unknown file format: " + file_format);
  }
  
  /* it->second is a pointer to the creator function. Calling it constructs and returns the appropriate OutputWriter object.*/
  return it->second();
}
