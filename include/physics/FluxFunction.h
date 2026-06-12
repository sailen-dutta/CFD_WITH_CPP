#pragma once

class FluxFunction{
    public:
        virtual ~FluxFunction() = default;
        virtual double flux(double u) const = 0;
        virtual double maxWaveSpeed(double u) const = 0;
};
