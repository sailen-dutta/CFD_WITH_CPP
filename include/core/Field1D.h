#pragma once

#include "core/Grid1D.h"
#include "core/Vector.h"

class Field1D{
    public:
        /* Constructors */
        explicit Field1D(const Grid1D& grid, std::size_t num_variables, std::size_t numGhostCells = 0); /* numGhostCells = number of ghost cells per side. For 1D, numGhostCells = 1 */
        Field1D(const Field1D&) = default;
        Field1D& operator=(const Field1D&) = default;

        /* Capacity */
        std::size_t size() const noexcept;
	std::size_t numPhysicalCells() const noexcept;
	std::size_t numGhostCells() const noexcept;
        std::size_t numVariables() const noexcept;
	std::size_t physicalIndex(std::size_t i) const noexcept;

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
	std::size_t numGhostCells_;
};
