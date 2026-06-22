#pragma once

#include "core/Grid1D.h"
#include "core/Vector.h"

class Field1D{
    public:
        explicit Field1D(const Grid1D& grid);
        Field1D(const Field1D&) = default;
        Field1D& operator=(const Field1D&) = default;
        size_t size() const noexcept;
        double& operator[](size_t i);
        const double& operator[](size_t i) const;
        double at(size_t i) const;
        double value(size_t i) const;
        void fill(double value);
        const Grid1D& grid() const;
        const Vector& values() const;

    private:
        Grid1D grid_;
        Vector values_;
};