#pragma once
#include <memory>
#include <string>

class Reconstruction;
class SlopeLimiter;

class ReconstructionFactory {
	public:
		static std::unique_ptr<Reconstruction> create(const std::string& reconstruction_type, const SlopeLimiter& limiter);
};

