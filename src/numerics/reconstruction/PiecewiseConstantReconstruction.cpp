#include "numerics/reconstruction/PiecewiseConstantReconstruction.h"
#include "core/Field1D.h"
#include "core/Vector.h"

void PiecewiseConstantReconstruction::reconstruct(const Field1D& U, size_t interface, Vector& UL, Vector& UR) const{

    /* Interface is located between cell 'interface' and cell 'interface+1' */
    const std::size_t left  = interface;
    const std::size_t right = interface + 1;

    /* Piecewise constant approximation: interface states are equal to neighbouring cell averages */
    UL = U[left];
    UR = U[right];
}
