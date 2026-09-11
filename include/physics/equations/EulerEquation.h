#pragma once

#include "physics/equations/HyperbolicEquation.h"

class EulerEquation : public HyperbolicEquation {
	public:
		explicit EulerEquation(double gamma = 1.4);
		Vector flux(const Vector& U) const override;
		double maxWaveSpeed(const Vector& U) const override;
		std::size_t numVariables() const override;
		double gamma() const;
	private:
		double gamma_;
};
