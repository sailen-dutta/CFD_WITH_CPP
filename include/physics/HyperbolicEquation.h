#pragma once
#include <cstddef>

class HyperbolicEquation {
	public:
		virtual ~HyperbolicEquation() = default;
		
		/* Physical flux */
		virtual double flux(double u) const = 0;

		/* Max wave speed */
		virtual double maxWaveSpeed(double u) const = 0;

		/* No. of conserved variables */
		virtual std::size_t numVariables() const = 0;
};
