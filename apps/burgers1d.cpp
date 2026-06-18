#include "core/Grid1D.h"
#include "core/Field1D.h"
#include "physics/InitialConditions.h"
#include "physics/BurgersFlux.h"
#include "numerics/flux/RusanovFlux.h"
#include "numerics/spatial/FirstOrderFVOperator.h"
#include "numerics/time/ForwardEuler.h"
#include "io/CSVWriter.h"
#include "io/VTKWriter1D.h"
#include "io/OutputManager.h"

#include <iostream>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <cmath>

double computeDt(const Field1D& u, double cfl, double& umax){
    umax = 0.0;

    for (size_t i = 0; i < u.size(); ++i){
        umax = std::max(umax,std::abs(u[i]));
    }

    if (umax < 1e-12) return 1e-6;

    return cfl * u.grid().dx() / umax;


}

int main(){
    Grid1D grid(0.0, 1.0, 201);
    Field1D u(grid);

    InitialConditions::sinewave(u);

    BurgersFlux physical_flux;
    RusanovFlux numerical_flux(physical_flux);
    FirstOrderFVOperator spatial(numerical_flux);
    ForwardEuler integrator;

    try{
        OutputManager::initialize();
    }
    catch (const std::exception& e){
        std::cerr << "Output initialization failed: " << e.what() << "\n";
        return 1;
    }     

    const double CFL = 0.5;
    const double t_final = 0.2;
    double t = 0.0;

    std::cout << "========================================\n";
    std::cout << "      1D Burgers Equation Solver\n";
    std::cout << "========================================\n";
    std::cout << "Grid points      : " << grid.size() << "\n";
    std::cout << "Domain           : ["
            << grid.x0() << ", "
            << grid.x1() << "]\n";
    std::cout << "Initial condition: Sine Wave\n";
    std::cout << "Numerical Flux   : Rusanov\n";
    std::cout << "Time Integrator  : Forward Euler\n";
    std::cout << "CFL              : " << CFL << "\n";
    std::cout << "Final Time       : " << t_final << "\n";
    std::cout << "========================================\n\n";  

    int output_counter = 0;
    int step = 0;
    while (t < t_final){
        double umax;
        double dt = computeDt(u, CFL, umax);

        if (t + dt > t_final){
            dt = t_final - t;
        }

        VTKWriter1D::write(u,OutputManager::makeVTKFilename(output_counter++));

        integrator.advance(u, spatial, dt);

        t += dt;

        std::cout << "Step: " << std::setw(5) << step++ << " | Time: " << std::fixed << std::setprecision(6) << t << " | dt: " << dt << " | umax = " << umax << '\n';
    }

    VTKWriter1D::write(u, OutputManager::finalVTKFilename());

    std::cout << "\n========================================\n";
    std::cout << "Simulation complete.\n";
    std::cout << "Final time : " << t << "\n";
    std::cout << "Steps      : " << step << "\n";
    std::cout << "Output dir : output/\n";
    std::cout << "========================================\n";

    return 0;
}