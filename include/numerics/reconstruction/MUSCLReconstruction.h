#pragma once
#include "numerics/reconstruction/Reconstruction.h"

/* Second order MUSCL reconstruction
   Builds as linear profile inside each cell and reconstructs left and right states
   
   Uses a slope limiter to avoid oscillations near discontinuities
*/

class MUSCLReconstruction : public Reconstruction{
    public:
        void reconstruct(const Field1D& u, size_t interface, double& uL, double& uR) const override;
    
    private:
        /* Minmod slope limiter */
        double minmod(double a, double b) const;
};