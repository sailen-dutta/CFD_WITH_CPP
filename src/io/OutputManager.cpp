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

std::string OutputManager::makeFilename(int counter, const std::string& extension, const std::string& output_dir){
    std::ostringstream filename;

    filename << output_dir << "/solution_" << std::setw(4) << std::setfill('0') << counter << "." << extension;
    
    return filename.str();
}

std::string OutputManager::finalFilename(const std::string& extension, const std::string& output_dir){
    return output_dir + "/final." + extension;
}

std::string OutputManager::makeOutputDirectory(const std::string& root_dir, const std::string& equation, const std::string& time_integrator){
    return root_dir + "/" + equation + "/" + time_integrator;
}
