#pragma once
#include "io/writers/OutputWriter.h"
#include <memory>
#include <string>

class OutputWriterFactory {
    public:
        static std::unique_ptr<OutputWriter> create(const std::string& file_format);
};