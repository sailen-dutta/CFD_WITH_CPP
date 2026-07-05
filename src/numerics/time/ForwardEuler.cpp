#include "numerics/time/ForwardEuler.h"

void ForwardEuler :: advance(Field1D& u, const SpatialOperator& op, double dt) const {
    Field1D rhs(u.grid());
    op.computeRHS(u, rhs);

    for (size_t i = 0; i < u.size(); ++i){
        u[i] += dt * rhs[i];
    }
}