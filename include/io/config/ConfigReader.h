#pragma once

#include "core/SimulationConfig.h"
#include <string>

class ConfigReader {
    public:
        static SimulationConfig read(const std::string& filename);
};