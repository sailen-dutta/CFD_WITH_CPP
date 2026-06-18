#pragma once

#include "core/Field1D.h"
#include <string>

class VTKWriter1D {
    public:
        static void write(const Field1D& field, const std::string& filename);
};