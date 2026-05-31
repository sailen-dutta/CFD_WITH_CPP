#pragma once

#include "core/Grid1D.h"
#include "core/Vector.h"

class Field1D{
    public:
        explicit Field1D(const Grid1D& grid);
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