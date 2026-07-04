#include "numerics/reconstruction/MUSCLReconstruction.h"
#include "core/Field1D.h"

#include <cmath>
#include <algorithm>

double MUSCLReconstruction::minmod(double a, double b) const{
    /* Opposite signs indicate an extreme. Remove slope to avoid oscillations */
    if (a*b <= 0.0) return 0.0;

    /* Keep the smaller magnitude slope */
    return std::copysign(std::min(std::abs(a),std::abs(b)),a);
}

void MUSCLReconstruction::reconstruct(const Field1D& u, size_t interface, double& uL, double& uR) const {
    const size_t N = u.size();

    /* Interface is between cell i and cell i+1 */
    const size_t i = interface;
    const size_t ip1 = (i + 1) % N;

    /* Neighbours required for slopes */
    const size_t im1 = (i == 0) ? N - 1 : i - 1;
    const size_t ip2 = (i + 2) % N;

    /* Slope in cell i */
    double slope_i = minmod(u[i] - u[im1], u[ip1] - u[i]);

    /* Slope in cell i+1 */
    double slope_ip1 = minmod(u[ip1] - u[i], u[ip2] - u[ip1]);

    /* Reconstruct interface states */
    uL = u[i] + 0.5 * slope_i;
    uR = u[i] - 0.5 * slope_ip1;
}