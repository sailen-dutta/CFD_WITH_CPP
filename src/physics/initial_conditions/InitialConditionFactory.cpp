#include "physics/initial_conditions/InitialConditionFactory.h"
#include "core/Field1D.h"
#include "core/SimulationConfig.h"
#include "physics/initial_conditions/InitialConditions.h"

#include <stdexcept>
#include <string>
#include <unordered_map>

namespace{
    /********* Adapter Functions **********/
    /* Initial condition functions have different input parameters.
       For example:
       sinewave -----> 1 parameter
       gaussian -----> center, sigma
       square pulse -> start, end, value
       These adapter functions provide a common interface so that they can be stored in a lookup table using function pointers
    */
   void applySinewave(const SimulationConfig& cfg, Field1D& field){
    InitialConditions::sinewave(field);
   }

   void applyGaussian(const SimulationConfig& cfg, Field1D& field){
    InitialConditions::gaussian(field, cfg.gaussian.center, cfg.gaussian.sigma);
   }

   void applySquarePulse(const SimulationConfig& cfg, Field1D& field){
    InitialConditions::squarePulse(field, cfg.square_pulse.x_start, cfg.square_pulse.x_end, cfg.square_pulse.value);
   }

   /* Function pointer */
   using InitialConditionApplier = void (*)(const SimulationConfig& cfg, Field1D& field);

   /* Lookup table mapping initial condition names from config.json to the corresponding implementation */
   std::unordered_map<std::string, InitialConditionApplier> lookup_table = {
    {"sinewave",      applySinewave},
    {"gaussian",      applyGaussian},
    {"square_pulse",  applySquarePulse}
   }; 
}

void InitialConditionFactory::apply(const SimulationConfig& cfg, Field1D& field) {
    auto it = lookup_table.find(cfg.initial_condition);

    if (it == lookup_table.end()){
        throw std::runtime_error("Unknown initial condition: " + cfg.initial_condition);
    }

    it->second(cfg, field);
}