#pragma once
#include <string>

class OutputManager {
    public:
        static void initialize(const std::string& output_dir = "output");
        static std::string makeFilename(int counter, const std::string& extension, const std::string& output_dir = "output");
        static std::string finalFilename(const std::string& extension, const std::string& output_dir = "output");
        static std::string makeOutputDirectory(const std::string& root_dir, const std::string& equation, const std::string& flux, const std::string& reconstruction, const std::string& limiter, const std::string& time_integrator);
};