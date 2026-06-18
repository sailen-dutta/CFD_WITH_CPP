#include "numerics/spatial/FirstOrderFVOperator.h"

FirstOrderFVOperator::FirstOrderFVOperator(const NumericalFlux& flux) : flux_(flux) {}

void FirstOrderFVOperator::computeRHS(const Field1D& u, Field1D& rhs) const {
    double dx = u.grid().dx();
    size_t N = u.size();

    for (size_t i = 0; i < N; ++i){
        size_t im1 = (i == 0)? N - 1 : i - 1;
        size_t ip1 = (i + 1) % N;
        double F_right = flux_.compute(u[i], u[ip1]);
        double F_left = flux_.compute(u[im1], u[i]);
        rhs[i] = -(F_right - F_left) / dx; 
    }
}