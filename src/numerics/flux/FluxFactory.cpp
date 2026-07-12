#include "numerics/flux/FluxFactory.h"
#include "numerics/flux/NumericalFlux.h"
#include "numerics/flux/RusanovFlux.h"

#include <unordered_map>
#include <stdexcept>

namespace{
	std::unique_ptr<NumericalFlux> createRusanov(){
		return std::make_unique<RusanovFlux>();
	}

	using Creator = std::unique_ptr<NumericalFlux>(*)();

	std::unordered_map<std::string, Creator> registry = {
		{"rusanov", createRusanov}
	};
}

std::unique_ptr<NumericalFlux> FluxFactory::create(const std::string& flux_type){
	auto it = registry.find(flux_type);

	if (it == registry.end()){
		throw std::runtime_error("Unknown numerical flux type: " + flux_type);
	}

	return it->second();
}
