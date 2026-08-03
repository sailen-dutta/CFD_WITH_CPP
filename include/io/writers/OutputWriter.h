#pragma once
#include "core/Field1D.h"
#include <string>

class OutputWriter {
    public:
        virtual ~OutputWriter() = default;
        virtual void write(const Field1D& field, const std::string& filename) = 0;
        virtual std::string extension() const = 0;
};