#include "FTCS.h"

void FTCS::step(Field1D& u, double c, double dt){
    Field1D u_new = u;
    double dx = u.grid().dx();

    double coeff = c * dt / (2.0 * dx);

    for (size_t i = 0; i < u.size(); i++){
        size_t ip1, im1;
        /* Periodic left neighbour */
        if (i == 0) {
            im1 = u.size() - 1;
        }
        else{
            im1 = i - 1;
        }

        /* Periodic right neighbour */
        if (i == u.size() - 1){
            ip1 = 0;
        }
        else{
            ip1 = i + 1;
        }
        u_new[i] = u[i] - coeff * (u[ip1] - u[im1]);
    }
    u = u_new;
}