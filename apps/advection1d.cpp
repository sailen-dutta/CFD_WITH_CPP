#include "Field1D.h"
#include "Grid1D.h"
#include "InitialConditions.h"
#include "UpwindScheme.h"
#include "FTCS.h"
#include "CSVWriter.h"

#include <iostream>
#include <memory>
#include <iomanip>
#include <sstream>
//#include <filesystem>

int main(int argc, char* argv[]){

    /* Validate command line argument */
    if (argc < 2){
        std::cerr << "Usage: " << argv[0] << " <scheme>\n";
        return 1;
    }
    
    std::string scheme_name = argv[1];

    /* Grid */
    Grid1D grid(0.0, 1.0, 101);
    

    Field1D u(grid);
    u.fill(0.0);

    InitialConditions::squarePulse(u, 0.4, 0.6, 1.0);

    double c = 1.0;
    double dt = 0.001;
    double t_final = 0.2;
    
    /* No. of time steps */
    int nsteps = static_cast<int>(t_final/dt);

    /* Output every 10 steps */
    int output_frequency = 10;

    /* Numerical scheme */
    std::unique_ptr<AdvectionScheme> scheme;
    if (scheme_name == "upwind"){
        scheme = std::make_unique<UpwindScheme>();
    }
    else if (scheme_name == "ftcs"){
        scheme = std::make_unique<FTCS>();
    }
    else {
        std::cerr << "Unknown scheme: " << scheme_name << "\n";
        return 1;
    }
    
    std::cout << "Using scheme: " << scheme_name << "\n";

    /* Time integration loop */
    for (int step = 0; step <= nsteps; step++){

        /* Current time */
        double t = step * dt;        

        /* Print solver progress */
        std::cout << "Step: " << step << "/" << nsteps << ", time = " << std::fixed << std::setprecision(3) << t << "\n";

        /* Output solution */
        if (step % output_frequency == 0){
            std::ostringstream filename;
            filename << "output/solution_" << std::setw(4) << std::setfill('0') << step << ".csv";
            CSVWriter::write(u,filename.str());
        }

        /* Advance solution */
        scheme->step(u, c, dt);
    }


    return 0;
}