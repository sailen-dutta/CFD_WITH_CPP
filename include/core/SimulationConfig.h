#pragma once
#include <string>

struct GaussianConfig{
    double center = 0.5;    /* Default values */
    double sigma = 0.05;
};

struct SquarePulseConfig{
    double x_start = 0.25;  /* Default values */
    double x_end   = 0.50;
    double value   = 1.0;
};

struct SimulationConfig{
    double x0;
    double x1;
    int nx;

    double t_final;
    double cfl;

    std::string equation;
    std::string initial_condition;

    GaussianConfig gaussian;
    SquarePulseConfig square_pulse;

    std::string flux;
    std::string reconstruction;
    std::string limiter;
    std::string spatial_operator;
    std::string time_integrator;

    std::string output_format;
    int output_frequency;
    std::string output_directory;
};
