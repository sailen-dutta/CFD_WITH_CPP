#pragma once
#include <memory>
#include <string>

class NumericalFlux;
class FluxFunction;

class FluxFactory{
	public:
		static std::unique_ptr<NumericalFlux> create(const std::string& flux_type, const FluxFunction& flux_function);
};
