#include "UpwindScheme.h"

void UpwindScheme::step(Field1D& u, double c, double dt){
    Field1D u_new = u;
    double dx = u.grid().dx();
    double cfl = c * dt/dx;

    for (size_t i = 1; i < u.size(); i++){
        u_new[i] = u[i] - cfl * (u[i] - u[i-1]);
    }
    u = u_new;
}