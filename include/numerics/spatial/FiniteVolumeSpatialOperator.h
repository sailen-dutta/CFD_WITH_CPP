#pragma once

#include "numerics/spatial/SpatialOperator.h"
#include "numerics/flux/NumericalFlux.h"
#include "numerics/reconstruction/Reconstruction.h"
#include "physics/HyperbolicEquation.h"

/* Finite volume spatial operator: 
   Uses reconstruction to compute interface states, and numerical flux to compute interface fluxes */
class FiniteVolumeSpatialOperator : public SpatialOperator {
    public:
        FiniteVolumeSpatialOperator(const HyperbolicEquation& equation, const NumericalFlux& flux, const Reconstruction& reconstruction);
        void computeRHS(const Field1D& u, Field1D& rhs) const override;
    private:
        const HyperbolicEquation& equation_;
        const NumericalFlux& flux_;  
        const Reconstruction& reconstruction_;  
};