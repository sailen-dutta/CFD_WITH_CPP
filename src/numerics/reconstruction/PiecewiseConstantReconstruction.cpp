#include "numerics/reconstruction/PiecewiseConstantReconstruction.h"
#include "core/Field1D.h"
#include "core/Vector.h"

void PiecewiseConstantReconstruction::reconstruct(const Field1D& U, size_t interface, Vector& UL, Vector& UR) const{
    const std::size_t N = U.size();

    /* Interface is located between cell i and cell i+1 */
    const std::size_t left  = interface;
    const std::size_t right = (interface + 1) % N;

    /* Piecewise constant approximation: interface states are equal to neighbouring cell averages */
    UL = U[left];
    UR = U[right];
}