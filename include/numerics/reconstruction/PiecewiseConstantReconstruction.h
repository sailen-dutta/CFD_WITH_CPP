#pragma once
#include "numerics/reconstruction/Reconstruction.h"

/* First order reconstruction: Assumes the solution is constant inside each cell */
class PiecewiseConstantReconstruction : public Reconstruction {
    public:
        void reconstruct(const Field1D& U, size_t interface, Vector& UL, Vector& UR) const override;
};