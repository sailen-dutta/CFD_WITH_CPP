#include "numerics/reconstruction/PiecewiseConstantReconstruction.h"
#include "core/Field1D.h"

void PiecewiseConstantReconstruction::reconstruct(const Field1D& u, size_t interface, double& uL, double& uR) const{
    size_t N = u.size();

    /* Interface is located between cell i and cell i+1 */
    size_t left = interface;
    size_t right = (interface + 1) % N;

    /* Piecewise constant approximation: interface states are equal to neighbouring cell averages */
    uL = u[left];
    uR = u[right];
}