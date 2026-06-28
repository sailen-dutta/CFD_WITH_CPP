#include "core/Grid1D.h"
#include "core/Field1D.h"
#include "core/SimulationConfig.h"

#include "physics/initial_conditions/InitialConditions.h"
#include "physics/initial_conditions/InitialConditionFactory.h"
#include "physics/BurgersFlux.h"

#include "numerics/flux/RusanovFlux.h"
#include "numerics/spatial/FirstOrderFVOperator.h"
#include "numerics/time/ForwardEuler.h"
#include "numerics/time/RK2.h"
#include "numerics/time/SSPRK3.h"
#include "numerics/time/TimeIntegratorFactory.h"

#include "io/ConfigReader.h"
#include "io/OutputManager.h"
#include "io/OutputWriter.h"
#include "io/OutputWriterFactory.h"
#include "io/RunSummaryWriter.h"

#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cmath>
#include <memory>

double computeDt(const Field1D& u, double cfl, double& umax){
    umax = 0.0;

    for (size_t i = 0; i < u.size(); ++i){
        umax = std::max(umax,std::abs(u[i]));
    }

    if (umax < 1e-12) return 1e-6;

    return cfl * u.grid().dx() / umax;


}

int main(){
    SimulationConfig cfg;

    try{
        cfg = ConfigReader::read("../config/burgers.json");
    }
    catch(const std::exception& e){
        std::cerr << "Failed to read config: " << e.what() << "\n";
        return 1;
    }
    
    Grid1D grid(cfg.x0, cfg.x1, cfg.nx);
    Field1D u(grid);

    /* Initial condition */
    InitialConditionFactory::apply(cfg, u);    

    BurgersFlux physical_flux;
    RusanovFlux numerical_flux(physical_flux);
    FirstOrderFVOperator spatial(numerical_flux);
    
    auto time_integrator = TimeIntegratorFactory::create(cfg.time_integrator);

    /* Output */
    auto writer = OutputWriterFactory::create(cfg.output_format);
    auto extension = writer->extension();

    auto output_dir = OutputManager::makeOutputDirectory(cfg.output_directory, cfg.equation, cfg.time_integrator);

    try{
        OutputManager::initialize(output_dir);
    }
    catch (const std::exception& e){
        std::cerr << "Output initialization failed: " << e.what() << "\n";
        return 1;
    }    

    RunSummaryWriter::writeSummary(cfg, output_dir);
    
    std::cout << "========================================\n";
    std::cout << "      1D Burgers Equation Solver\n";
    std::cout << "========================================\n";
    std::cout << "Grid points        : " << grid.size() << "\n";
    std::cout << "Domain             : ["
            << grid.x0() << ", "
            << grid.x1() << "]\n";
    std::cout << "Initial condition  : " << cfg.initial_condition << "\n";
    std::cout << "Numerical Flux     : " << cfg.flux << "\n";
    std::cout << "Time Integrator    : " << cfg.time_integrator << "\n";
    std::cout << "CFL                : " << cfg.cfl << "\n";
    std::cout << "Final Time         : " << cfg.t_final << "\n";
    std::cout << "========================================\n\n";  

    double t = 0.0;
    int output_counter = 0;
    int step = 0;

    /* Time loop */
    while (t < cfg.t_final){
        double umax;
        double dt = computeDt(u, cfg.cfl, umax);

        if (t + dt > cfg.t_final){
            dt = cfg.t_final - t;
        }

        if (step % cfg.output_frequency == 0){
            writer->write(u, OutputManager::makeFilename(output_counter++, extension, output_dir));
        }       

        time_integrator->advance(u, spatial, dt);

        t += dt;

        std::cout << "Step: " << std::setw(5) << step++ << " | Time: " << std::fixed << std::setprecision(6) << t << " | dt: " << dt << " | umax = " << umax << '\n';
        ++step;
    }

    writer->write(u, OutputManager::finalFilename(extension, output_dir));

    std::cout << "\n========================================\n";
    std::cout << "Simulation complete.\n";
    std::cout << "Final time : " << t << "\n";
    std::cout << "Steps      : " << step << "\n";
    std::cout << "Output dir : " << output_dir << "\n";
    std::cout << "========================================\n";

    return 0;
}