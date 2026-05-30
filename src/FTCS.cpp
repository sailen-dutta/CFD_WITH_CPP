#include "FTCS.h"

void FTCS::step(Field1D& u, double c, double dt){
    Field1D u_new = u;
    double dx = u.grid().dx();

    double coeff = c * dt / (2.0 * dx);

    for (size_t i = 1; i < u.size() - 1; i++){
        u_new[i] = u[i] - coeff * (u[i+1] - u[i-1]);
    }
    u = u_new;
}