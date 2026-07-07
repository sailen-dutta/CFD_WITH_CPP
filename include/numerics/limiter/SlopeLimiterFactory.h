#pragma once
#include <memory>
#include <string>

class SlopeLimiter;

/* Factory responsible for creating slope limiters from run time config */
class SlopeLimiterFactory {
    public:
        static std::unique_ptr<SlopeLimiter> create(const std::string& limiter_type);
};