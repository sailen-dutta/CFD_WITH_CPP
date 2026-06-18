#include "io/OutputManager.h"
#include <filesystem>
#include <sstream>
#include <iomanip>

namespace fs = std::filesystem;

void OutputManager::initialize(const std::string& output_dir){
    if (fs::exists(output_dir)){
        fs::remove_all(output_dir);
    }

    fs::create_directories(output_dir);
}

std::string OutputManager::makeFilename(int counter, const std::string& output_dir){
    std::ostringstream filename;

    filename << output_dir << "/solution_" << std::setw(4) << std::setfill('0') << counter << ".csv";
    
    return filename.str();
}

std::string OutputManager::finalFilename(const std::string& output_dir){
    return output_dir + "/final.csv";
}

std::string OutputManager::makeVTKFilename(int counter, const std::string& output_dir){
    std::ostringstream filename;

    filename << output_dir << "/solution_" << std::setw(4) << std::setfill('0') << counter << ".vtk";

    return filename.str();
}

std::string OutputManager::finalVTKFilename(const std::string& output_dir){
    return output_dir + "/final.vtk";
}
