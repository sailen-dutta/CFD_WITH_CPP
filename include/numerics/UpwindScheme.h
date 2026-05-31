#pragma once
#include "numerics/AdvectionScheme.h"

class UpwindScheme : public AdvectionScheme {
    public:
        void step(Field1D& u, double c, double dt) override;
};

