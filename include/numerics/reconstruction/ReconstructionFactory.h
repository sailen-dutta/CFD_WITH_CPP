#pragma once
#include <memory>
#include <string>

class Reconstruction;

class ReconstructionFactory {
	public:
		static std::unique_ptr<Reconstruction> create(const std::string& type);
};

