#include "numerics/spatial/FiniteVolumeSpatialOperator.h"

FiniteVolumeSpatialOperator::FiniteVolumeSpatialOperator(const HyperbolicEquation& equation, const NumericalFlux& flux, const Reconstruction& reconstruction) : equation_(equation), flux_(flux), reconstruction_(reconstruction) {}

void FiniteVolumeSpatialOperator::computeRHS(const Field1D& u, Field1D& rhs) const {
    const double dx = u.grid().dx();
    const std::size_t N = u.size();
    const std::size_t numVar = equation_.numVariables();

    for (std::size_t i = 0; i < N; ++i){
        /*UL_left  = value approaching the left interface from the left
          UL_right = value approaching the right interface from the left
          UR_left  = value approaching the left interface from the right
          UR_right = value approaching the right interface from the right*/
        Vector UL_left(numVar), UL_right(numVar), UR_left(numVar), UR_right(numVar);

        /* Interface i+1/2 */
        reconstruction_.reconstruct(u,i,UL_right,UR_right);

        const std::size_t left_interface = (i == 0) ? N - 1 : i - 1;
        
        /* Interface i-1/2 */
        reconstruction_.reconstruct(u,left_interface,UL_left, UR_left);

        Vector F_right = flux_.compute(UL_right, UR_right, equation_);
        Vector F_left  = flux_.compute(UL_left, UR_left, equation_);

        rhs[i] = -(F_right - F_left) / dx;
    }
}