#include "io/RunSummaryWriter.h"
#include "core/SimulationConfig.h"
#include <fstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

void RunSummaryWriter::writeSummary(const SimulationConfig& cfg, const std::string& output_dir){
    json j;

    j["mesh"]["x0"]                     = cfg.x0;
    j["mesh"]["x1"]                     = cfg.x1;
    j["mesh"]["nx"]                     = cfg.nx;
    j["simulation"]["t_final"]          = cfg.t_final;
    j["simulation"]["cfl"]              = cfg.cfl;
    j["physics"]["equation"]            = cfg.equation;
    j["initial_condition"]["type"]      = cfg.initial_condition;
    j["numerics"]["flux"]               = cfg.flux;
    j["numerics"]["reconstruction"]     = cfg.reconstruction;
    j["numerics"]["spatial_operator"]   = cfg.spatial_operator;
    j["numerics"]["time_integrator"]    = cfg.time_integrator;
    j["output"]["format"]               = cfg.output_format;

    std::ofstream out(output_dir + "/run_summary.json");

    out << j.dump(4);
}