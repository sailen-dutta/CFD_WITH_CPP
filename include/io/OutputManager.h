#pragma once
#include <string>

class OutputManager {
    public:
        static void initialize(const std::string& output_dir = "output");
        static std::string makeFilename(int counter, const std::string& output_dir = "output");
        static std::string finalFilename(const std::string& output_dir = "output");
        static std::string makeVTKFilename(int counter, const std::string& output_dir = "output");
        static std::string finalVTKFilename(const std::string& output_dir = "output");
};