#include "numerics/boundary/PeriodicBC.h"

void PeriodicBC::apply(Field1D& field) const {
	const std::size_t N = field.numPhysicalCells();
	const std::size_t ng = field.numGhostCells();

	if (ng == 0) {
		return;
	}

	/* Left ghost cells <- rightmost physical cells */
	for (std::size_t g = 0; g < ng; ++g) {
		field[g] = field[N + g];
	}
	
	/* Right ghost cells <- leftmost physical cells */
	for (std::size_t g = 0; g < ng; ++g) {
		field[ng + N + g] = field[ng + g];
	}
}

