#include "numerics/time/RK2.h"

void RK2::advance(Field1D& u, const SpatialOperator& op, double dt) const{
    Field1D u0(u);
    Field1D u1(u);

    Field1D k1(u.grid());
    Field1D k2(u.grid());

    /* Stage 1 */
    op.computeRHS(u0, k1);

    for (size_t i = 0; i < u.size(); ++i){
        u1[i] = u0[i] + dt * k1[i];
    }

    /* Stage 2 */
    op.computeRHS(u1, k2);

    for (size_t i = 0; i < u.size(); ++i){
        u[i] = u0[i] + 0.5 * dt * (k1[i] + k2[i]);
    }
}