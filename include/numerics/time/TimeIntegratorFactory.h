#pragma once
#include <memory>
#include <string>

class TimeIntegrator;

class TimeIntegratorFactory {
    public:
        static std::unique_ptr<TimeIntegrator> create(const std::string& integrator_type);
};