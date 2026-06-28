#include "numerics/time/TimeIntegratorFactory.h"
#include "numerics/time/ForwardEuler.h"
#include "numerics/time/RK2.h"
#include "numerics/time/SSPRK3.h"
#include <stdexcept>
#include <unordered_map>
#include <memory>
#include <string>

namespace {
    std::unique_ptr<TimeIntegrator> createForwardEuler(){
        return std::make_unique<ForwardEuler>();
    }

    std::unique_ptr<TimeIntegrator> createRK2() {
        return std::make_unique<RK2>();
    }

    std::unique_ptr<TimeIntegrator> createSSPRK3() {
        return std::make_unique<SSPRK3>();
    }

    using Creator = std::unique_ptr<TimeIntegrator> (*)();

    std::unordered_map<std::string, Creator> lookup_table = {
        {"forward_euler", createForwardEuler},
        {"rk2",           createRK2},
        {"ssprk3",        createSSPRK3}
    };
}

std::unique_ptr<TimeIntegrator> TimeIntegratorFactory::create(const std::string& integrator_type){
    auto it = lookup_table.find(integrator_type);

    if (it == lookup_table.end()){
        throw std::runtime_error("Unknown time integrator type: " + integrator_type);
    }

    return it->second();
}