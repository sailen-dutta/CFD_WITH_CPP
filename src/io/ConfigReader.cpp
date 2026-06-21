#include "io/ConfigReader.h"
#include <fstream>
#include <stdexcept>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

SimulationConfig ConfigReader::read(const std::string& filename){
    std::ifstream file(filename);

    if (!file){
        throw std::runtime_error("Cannot open config file.");        
    }

    json j;
    file >> j;

    SimulationConfig cfg;

    cfg.x0                  = j["mesh"]["x0"];
    cfg.x1                  = j["mesh"]["x1"];
    cfg.nx                  = j["mesh"]["nx"];
    cfg.t_final             = j["simulation"]["t_final"];
    cfg.cfl                 = j["simulation"]["cfl"];   
    cfg.equation            = j["physics"]["equation"];
    cfg.initial_condition   = j["initial_condition"]["type"];
    cfg.flux                = j["numerics"]["flux"];
    cfg.spatial_operator    = j["numerics"]["spatial_operator"];
    cfg.time_integrator     = j["numerics"]["time_integrator"];
    cfg.output_format       = j["output"]["format"];
    cfg.output_frequency    = j["output"]["frequency"];
    cfg.output_directory    = j["output"]["directory"];

    return cfg;
}
