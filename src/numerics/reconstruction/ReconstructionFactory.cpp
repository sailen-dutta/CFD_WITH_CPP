#include "numerics/reconstruction/ReconstructionFactory.h"
#include "numerics/reconstruction/Reconstruction.h"
#include "numerics/reconstruction/PiecewiseConstantReconstruction.h"
#include "numerics/reconstruction/MUSCLReconstruction.h"

#include <unordered_map>
#include <stdexcept>

namespace{
	/* Creator functions */
	std::unique_ptr<Reconstruction> createPiecewiseConstant(){
		return std::make_unique<PiecewiseConstantReconstruction>();
	}

	std::unique_ptr<Reconstruction> createMUSCL(){
		return std::make_unique<MUSCLReconstruction>();
	}

	using Creator = std::unique_ptr<Reconstruction>(*)();

	std::unordered_map<std::string, Creator> registry = {
		{"piecewise_constant", createPiecewiseConstant},
		{"muscl"             , createMUSCL            }
	};
}

std::unique_ptr<Reconstruction> ReconstructionFactory::create(const std::string& type){
	auto it = registry.find(type);

	if (it == registry.end()){
		throw std::runtime_error("Unknown reconstruction type: " + type);
	}

	return it->second();
}


