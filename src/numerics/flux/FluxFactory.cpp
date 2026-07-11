#include "numerics/flux/FluxFactory.h"
#include "numerics/flux/NumericalFlux.h"
#include "numerics/flux/RusanovFlux.h"
#include "physics/FluxFunction.h"
#include <unordered_map>
#include <stdexcept>

namespace{
	std::unique_ptr<NumericalFlux> createRusanov(const FluxFunction& flux_function){
		return std::make_unique<RusanovFlux>(flux_function);
	}

	using Creator = std::unique_ptr<NumericalFlux>(*)(const FluxFunction&);

	std::unordered_map<std::string, Creator> registry = {
		{"rusanov", createRusanov}
	};
}

std::unique_ptr<NumericalFlux> FluxFactory::create(const std::string& flux_type, const FluxFunction& flux_function){
	auto it = registry.find(flux_type);

	if (it == registry.end()){
		throw std::runtime_error("Unknown numerical flux type: " + flux_type);
	}

	return it->second(flux_function);
}
