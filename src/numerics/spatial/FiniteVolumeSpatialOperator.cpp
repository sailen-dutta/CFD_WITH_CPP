#include "numerics/spatial/FiniteVolumeSpatialOperator.h"

FiniteVolumeSpatialOperator::FiniteVolumeSpatialOperator(const HyperbolicEquation& equation, const NumericalFlux& flux, const Reconstruction& reconstruction) : equation_(equation), flux_(flux), reconstruction_(reconstruction) {}

void FiniteVolumeSpatialOperator::computeRHS(const Field1D& u, Field1D& rhs) const {
    double dx = u.grid().dx();
    size_t N = u.size();

    for (size_t i = 0; i < N; ++i){
        /*uL_left  = value approaching the left interface from the left
          uL_right = value approaching the right interface from the left
          uR_left  = value approaching the left interface from the right
          uR_right = value approaching the right interface from the right*/
        double uL_left, uL_right, uR_left, uR_right;

        /* Interface i+1/2 */
        reconstruction_.reconstruct(u,i,uL_right,uR_right);

        size_t left_interface = (i == 0) ? N - 1 : i - 1;
        
        /* Interface i-1/2 */
        reconstruction_.reconstruct(u,left_interface,uL_left, uR_left);

        double F_right = flux_.compute(uL_right, uR_right, equation_);
        double F_left = flux_.compute(uL_left, uR_left, equation_);

        rhs[i] = -(F_right - F_left) / dx;
    }
}