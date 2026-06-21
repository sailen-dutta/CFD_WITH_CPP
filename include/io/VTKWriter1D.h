#pragma once

#include "core/Field1D.h"
#include "io/OutputWriter.h"
#include <string>

class VTKWriter1D : public OutputWriter {
    public:
        void write(const Field1D& field, const std::string& filename) override;
        std::string extension() const override;
};