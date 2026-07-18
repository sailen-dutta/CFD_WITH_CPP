#include "numerics/reconstruction/MUSCLReconstruction.h"
#include "numerics/limiter/SlopeLimiter.h"
#include "core/Field1D.h"

#include <cmath>
#include <algorithm>

MUSCLReconstruction::MUSCLReconstruction(const SlopeLimiter& limiter) : limiter_(limiter){}

void MUSCLReconstruction::reconstruct(const Field1D& U, size_t interface, Vector& UL, Vector& UR) const {
    const std::size_t N = U.size();
    const std::size_t numVar = U.numVariables();

    /* Interface is between cell i and cell i+1 */
    const std::size_t i   = interface;
    const std::size_t ip1 = (i + 1) % N;

    /* Neighbours required for slopes */
    const std::size_t im1 = (i == 0) ? N - 1 : i - 1;
    const std::size_t ip2 = (i + 2) % N;

    /* slope_i stores the limited slope of every conserved variable in cell i.
        
        For the Euler equations:
        U[i]      = [ρ, ρu, E]
        slope_i   = [dρ, d(ρu), dE]
    */
    Vector slope_i(numVar);
    Vector slope_ip1(numVar);
    
    /* U is a 1D field of solution states.
    *
    * U[i]    -> conserved state stored in cell i (Vector)
    * U[i][k] -> kth conserved variable in cell i (double)
    *
    * Example (Euler):
    *   U[i]    = [ρ, ρu, E]
    *   U[i][0] = ρ
    *   U[i][1] = ρu
    *   U[i][2] = E
    */
    for (std::size_t k = 0; k < numVar; ++k){
        /* Slope in cell i */
        slope_i[k] = limiter_.limit(U[i][k] - U[im1][k], U[ip1][k] - U[i][k]);
        /* Slope in cell i + 1 */
        slope_ip1[k] = limiter_.limit(U[ip1][k] - U[i][k], U[ip2][k] - U[ip1][k]);
    }  

    /* Reconstruct the left and right states at the interface.
    *
    * UL is the state approaching the interface from cell i.
    * UR is the state approaching the interface from cell i+1.
    *
    * Both UL and UR contain all conserved variables.
    */
        UL = U[i] + 0.5 * slope_i;
        UR = U[ip1] - 0.5 * slope_ip1;
}