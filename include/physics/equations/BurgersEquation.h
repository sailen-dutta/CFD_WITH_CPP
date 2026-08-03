#pragma once

#include "physics/equations/HyperbolicEquation.h"
#include <cmath>

class BurgersEquation : public HyperbolicEquation {
	public:
		Vector flux(const Vector& U) const override;
		double maxWaveSpeed(const Vector& U) const override;
		std::size_t numVariables() const override {
			return 1;
		}
};
