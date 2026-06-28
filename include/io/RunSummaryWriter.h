#pragma once
#include <string>

struct SimulationConfig;

class RunSummaryWriter{
    public:
        static void writeSummary(const SimulationConfig& cfg, const std::string& output_dir);
};