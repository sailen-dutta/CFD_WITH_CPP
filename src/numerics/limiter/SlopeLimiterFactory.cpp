#include "numerics/limiter/SlopeLimiterFactory.h"
#include "numerics/limiter/SlopeLimiter.h"
#include "numerics/limiter/MinmodLimiter.h"
#include "numerics/limiter/VanLeerLimiter.h"
#include "numerics/limiter/SuperbeeLimiter.h"
#include "numerics/limiter/UnlimitedLimiter.h"

#include <stdexcept>
#include <unordered_map>

namespace {
    std::unique_ptr<SlopeLimiter> createUnlimited(){
        return std::make_unique<UnlimitedLimiter>();
    }

    std::unique_ptr<SlopeLimiter> createMinmod(){
        return std::make_unique<MinmodLimiter>();
    }

    std::unique_ptr<SlopeLimiter> createVanLeer() {
        return std::make_unique<VanLeerLimiter>();
    }

    std::unique_ptr<SlopeLimiter> createSuperbee() {
        return std::make_unique<SuperbeeLimiter>();
    }

    using Creator = std::unique_ptr<SlopeLimiter> (*)();

    std::unordered_map<std::string, Creator> lookup_table = {
        {"unlimited", createUnlimited},
        {"minmod", createMinmod},
        {"vanleer", createVanLeer},
        {"superbee", createSuperbee}
    };
}

std::unique_ptr<SlopeLimiter> SlopeLimiterFactory::create(const std::string& limiter_type){
    auto it = lookup_table.find(limiter_type);

    if (it == lookup_table.end()){
        throw std::runtime_error("Unknown limiter: " + limiter_type);
    }

    return it->second();
}