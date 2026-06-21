#include "physics/initial_conditions/InitialConditionFactory.h"
#include "core/Field1D.h"
#include "core/SimulationConfig.h"
#include "physics/initial_conditions/InitialConditions.h"

#include <stdexcept>

void InitialConditionFactory::apply(const SimulationConfig& cfg, Field1D& field) {
    if (cfg.initial_condition == "sinewave"){
        InitialConditions::sinewave(field);
    }
    else if (cfg.initial_condition == "gaussian"){
        InitialConditions::gaussian(field, cfg.gaussian.center, cfg.gaussian.sigma);
    }
    else if (cfg.initial_condition == "square_pulse"){
        InitialConditions::squarePulse(field, cfg.square_pulse.x_start, cfg.square_pulse.x_end, cfg.square_pulse.value);
    }
    else{
        throw std::runtime_error("Unknown initial condition: " + cfg.initial_condition);
    }
}