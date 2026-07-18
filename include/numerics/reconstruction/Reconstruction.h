#pragma once
#include <cstddef>

class Field1D;
class Vector;

class Reconstruction {
    public:
        virtual ~Reconstruction() = default;

        /* Compute left and right states at a cell interface 
           Input:
                u -----------> Cell Averaged solution
                interface ---> Interface index. 
            
            Output:
                uL ----------> Value reconstructed from left cell
                uR ----------> Value reconstructed from right cell
        */
        virtual void reconstruct(const Field1D& U, size_t interface, Vector& UL, Vector& UR) const = 0;
};  
