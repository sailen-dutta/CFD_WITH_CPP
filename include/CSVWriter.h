#pragma once

#include "Field1D.h"
#include <string>

class CSVWriter{
    public:
        static void write(const Field1D& field, const std::string& filename);
};