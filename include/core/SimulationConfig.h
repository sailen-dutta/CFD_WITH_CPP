#pragma once
#include <string>

struct SimulationConfig{
    double x0;
    double x1;
    int nx;

    double t_final;
    double cfl;

    std::string equation;
    std::string initial_condition;

    std::string flux;
    std::string spatial_operator;
    std::string time_integrator;

    std::string output_format;
    int output_frequency;
    std::string output_directory;
};