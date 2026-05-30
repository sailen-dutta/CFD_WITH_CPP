#pragma once

#include "Field1D.h"

class AdvectionScheme{
    public:
        virtual ~AdvectionScheme() = default;
        virtual void step(Field1D& u, double c, double dt) = 0;
};