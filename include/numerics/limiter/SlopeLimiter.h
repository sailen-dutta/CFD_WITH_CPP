#pragma once

/* Base class for Slope limiters */
class SlopeLimiter {
    public:
        virtual ~SlopeLimiter() = default;
        virtual double limit(double left, double right) const = 0;        
};