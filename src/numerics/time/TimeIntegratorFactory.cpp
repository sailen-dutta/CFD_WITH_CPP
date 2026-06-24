#include "numerics/time/TimeIntegratorFactory.h"
#include "numerics/time/ForwardEuler.h"
#include "numerics/time/RK2.h"
#include "numerics/time/SSPRK3.h"
#include <stdexcept>

std::unique_ptr<TimeIntegrator> TimeIntegratorFactory::create(const std::string& integrator_type){
    if (integrator_type == "forward_euler"){
        return std::make_unique<ForwardEuler>();
    }
    else if (integrator_type == "rk2"){
        return std::make_unique<RK2>();
    }
    else if (integrator_type == "ssprk3"){
        return std::make_unique<SSPRK3>();
    }
    else{
        throw std::runtime_error("Unknown time integrator: " + integrator_type);
    }
}