#pragma once

class Field1D;              /* Forward declaration */
struct SimulationConfig;

class InitialConditionFactory{
    public:
        static void apply(const SimulationConfig& cfg, Field1D& field);
};