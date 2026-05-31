#include "UpwindScheme.h"

void UpwindScheme::step(Field1D& u, double c, double dt){
    Field1D u_new = u;
    double dx = u.grid().dx();
    double cfl = c * dt/dx;

    for (size_t i = 0; i < u.size(); i++){
        /* Periodic Boundary Condition */
        std::size_t im1;
        if (i == 0) { 
            im1 = u.size() - 1; 
        } else {
             im1 = i - 1; 
        }
        u_new[i] = u[i] - cfl * (u[i] - u[im1]);
    }
    u = u_new;
}