#pragma once

#include "numerics/spatial/SpatialOperator.h"
#include "numerics/flux/NumericalFlux.h"
#include "numerics/reconstruction/PiecewiseConstantReconstruction.h"

/* Finite volume spatial operator: 
   Uses reconstruction to compute interface states, and numerical flux to compute interface fluxes */
class FiniteVolumeSpatialOperator : public SpatialOperator {
    public:
        explicit FiniteVolumeSpatialOperator(const NumericalFlux& flux, const Reconstruction& reconstruction);
        void computeRHS(const Field1D& u, Field1D& rhs) const override;
    private:
        const NumericalFlux& flux_;  
        const Reconstruction& reconstruction_;  
};