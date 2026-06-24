#include "numerics/time/SSPRK3.h"

void SSPRK3::advance(Field1D& u, const FiniteVolumeOperator& op, double dt) const {
    Field1D u0(u);
    Field1D u1(u);
    Field1D u2(u);

    Field1D rhs(u.grid());

    /* Stage 1 */
    op.computeRHS(u0, rhs);

    for (size_t i = 0; i < u.size(); ++i){
        u1[i] = u0[i] + dt * rhs[i];
    }

    /* Stage 2 */
    op.computeRHS(u1, rhs);

    for (size_t i = 0; i < u.size(); ++i){
        u2[i] = 0.75 * u0[i] + 0.25 * (u1[i] + dt * rhs[i]);
    }

    /* Stage 3 */
    op.computeRHS(u2, rhs);

    for (size_t i = 0; i < u.size(); ++i){
        u[i] = (1.0 / 3.0) * u0[i] + (2.0 / 3.0) * (u2[i] + dt * rhs[i]);
    }

}