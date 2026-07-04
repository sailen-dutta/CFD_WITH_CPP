#pragma once
#include "numerics/reconstruction/Reconstruction.h"

/* First order reconstruction: Assumes the solution is constant inside each cell */
class PiecewiseConstantReconstruction : public Reconstruction {
    void reconstruct(const Field1D& u, size_t interface, double& uL, double& uR) const override;
};