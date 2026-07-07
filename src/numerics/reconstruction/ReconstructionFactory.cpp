#include "numerics/reconstruction/ReconstructionFactory.h"
#include "numerics/reconstruction/Reconstruction.h"
#include "numerics/reconstruction/PiecewiseConstantReconstruction.h"
#include "numerics/reconstruction/MUSCLReconstruction.h"

#include <unordered_map>
#include <stdexcept>

namespace{
	/* Creator functions */
	std::unique_ptr<Reconstruction> createPiecewiseConstant(const SlopeLimiter& limiter){
		return std::make_unique<PiecewiseConstantReconstruction>();
	}

	std::unique_ptr<Reconstruction> createMUSCL(const SlopeLimiter& limiter){
		return std::make_unique<MUSCLReconstruction>(limiter);
	}

	using Creator = std::unique_ptr<Reconstruction>(*)(const SlopeLimiter&);

	std::unordered_map<std::string, Creator> registry = {
		{"piecewise_constant", createPiecewiseConstant},
		{"muscl"             , createMUSCL            }
	};
}

std::unique_ptr<Reconstruction> ReconstructionFactory::create(const std::string& reconstruction_type, const SlopeLimiter& limiter){
	auto it = registry.find(reconstruction_type);

	if (it == registry.end()){
		throw std::runtime_error("Unknown reconstruction type: " + reconstruction_type);
	}

	return it->second(limiter);
}


