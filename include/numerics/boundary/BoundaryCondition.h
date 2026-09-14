#pragma once

#include "core/Field1D.h"

class BoundaryCondition {
	public:
		virtual ~BoundaryCondition() = default;
		virtual void apply(Field1D& field) const = 0;
};

