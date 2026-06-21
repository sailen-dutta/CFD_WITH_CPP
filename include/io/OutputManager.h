#pragma once
#include <string>

class OutputManager {
    public:
        static void initialize(const std::string& output_dir = "output");
        static std::string makeFilename(int counter, const std::string& extension, const std::string& output_dir = "output");
        static std::string finalFilename(const std::string& extension, const std::string& output_dir = "output");
};