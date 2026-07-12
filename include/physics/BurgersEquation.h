#pragma once

#include "physics/HyperbolicEquation.h"
#include <cmath>

class BurgersEquation : public HyperbolicEquation {
	public:
		double flux(double u) const override;
		double maxWaveSpeed(double u) const override;
		std::size_t numVariables() const override {
			return 1;
		}
};
