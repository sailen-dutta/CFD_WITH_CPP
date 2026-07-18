#pragma once

#include "core/Grid1D.h"
#include "core/Vector.h"

class Field1D{
    public:
        /* Constructors */
        explicit Field1D(const Grid1D& grid, std::size_t num_variables);
        Field1D(const Field1D&) = default;
        Field1D& operator=(const Field1D&) = default;

        /* Capacity */
        std::size_t size() const noexcept;
        std::size_t numVariables() const noexcept;

        /* Element access */
        Vector& operator[](std::size_t i);
        const Vector& operator[](std::size_t i) const;
        Vector& at(std::size_t i);
        const Vector& at(std::size_t i) const;

        /* Utility */
        void fill(double value);

        /* Access */
        const Grid1D& grid() const;       

    private:
        Grid1D grid_;
        std::vector<Vector> values_;
};