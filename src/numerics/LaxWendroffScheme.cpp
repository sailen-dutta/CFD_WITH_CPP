#include "numerics/LaxWendroffScheme.h"

void LaxWendroffScheme::step(Field1D& u, double c, double dt){
    Field1D u_new = u;
    double dx = u.grid().dx();
    double cfl = c * dt / dx;

    for (size_t i = 0; i < u.size(); i++){
        size_t im1, ip1;

        if (i == 0){
            im1 = u.size() - 1;
        }
        else {
            im1 = i - 1;
        }

        if (i == u.size() - 1){
            ip1 = 0;
        }
        else{
            ip1 = i + 1;
        }

        u_new[i] = u[i] - 0.5 * cfl * (u[ip1] - u[im1]) + 0.5 * cfl * cfl * (u[ip1] - 2 * u[i] + u[im1]);
    }
    u = u_new;
}