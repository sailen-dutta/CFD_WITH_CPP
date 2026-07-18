#pragma once
#include "numerics/reconstruction/Reconstruction.h"

class SlopeLimiter;

/* Second order MUSCL reconstruction
   Builds as linear profile inside each cell and reconstructs left and right states
   
   Uses a slope limiter to avoid oscillations near discontinuities
*/
class MUSCLReconstruction : public Reconstruction{
    public:
        explicit MUSCLReconstruction(const SlopeLimiter& limiter);
        void reconstruct(const Field1D& U, size_t interface, Vector& UL, Vector& UR) const override;
    
    private:
        /* Slope limiter */
        const SlopeLimiter& limiter_;
};