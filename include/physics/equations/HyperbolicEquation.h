#pragma once

#include "core/Vector.h"
#include <cstddef>

class HyperbolicEquation {
	public:
		virtual ~HyperbolicEquation() = default;
		
		/* Physical flux */
		virtual Vector flux(const Vector& U) const = 0;

		/* Max wave speed */
		virtual double maxWaveSpeed(const Vector& U) const = 0;

		/* No. of conserved variables */
		virtual std::size_t numVariables() const = 0;
};
