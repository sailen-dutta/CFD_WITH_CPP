#pragma once

#include "numerics/spatial/FiniteVolumeOperator.h"
#include "numerics/flux/NumericalFlux.h"

class FirstOrderFVOperator : public FiniteVolumeOperator {
    public:
        explicit FirstOrderFVOperator(const NumericalFlux& flux);
        void computeRHS(const Field1D& u, Field1D& rhs) const override;
    private:
        const NumericalFlux& flux_;    
};