#include "numerics/spatial/FiniteVolumeSpatialOperator.h"

FiniteVolumeSpatialOperator::FiniteVolumeSpatialOperator(const HyperbolicEquation& equation, const NumericalFlux& flux, const Reconstruction& reconstruction) : equation_(equation), flux_(flux), reconstruction_(reconstruction) {}

void FiniteVolumeSpatialOperator::computeRHS(const Field1D& u, Field1D& rhs) const {
	const double dx = u.grid().dx();
	const std::size_t N = u.numPhysicalCells();
	const std::size_t numVar = equation_.numVariables();

	for (std::size_t i = 0; i < N; ++i) {
		const std::size_t si = u.physicalIndex(i);
		
		/* UL_left = State approaching the left interface from the left
		 * UR_left = State approaching the left interface from the right
		 * UL_right = State approaching the right interface from the left
		 * UL_left = State approaching the right interface from the right
		 */ 
		Vector UL_left(numVar);
		Vector UL_right(numVar);
		Vector UR_left(numVar);
		Vector UR_right(numVar);

		/* Right interface: Between physical cell i and i+1 */
		reconstruction_.reconstruct(u, si, UL_right, UR_right);

		/* Left interface: Between physical cell i and i-1 */
		reconstruction_.reconstruct(u, si-1, UL_left, UR_left);

		Vector F_right = flux_.compute(UL_right, UR_right, equation_);
		Vector F_left = flux_.compute(UL_left, UR_left, equation_);

		rhs[si] = -(F_right - F_left) / dx;
	}
}

