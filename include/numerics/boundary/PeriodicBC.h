#pragma once

#include "numerics/boundary/BoundaryCondition.h"

class PeriodicBC : public BoundaryCondition {
	public:
		void apply(Field1D& field) const override;
};


