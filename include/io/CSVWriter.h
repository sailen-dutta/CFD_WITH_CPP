#pragma once

#include "core/Field1D.h"
#include "io/OutputWriter.h"
#include <string>

class CSVWriter : public OutputWriter{
    public:
        void write(const Field1D& field, const std::string& filename);
        std::string extension() const override;
};