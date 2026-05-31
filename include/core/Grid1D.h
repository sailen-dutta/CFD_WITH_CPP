#pragma once

#include "core/Vector.h"
#include <cstddef>

class Grid1D{
    public:
        Grid1D(double x0, double x1, size_t nx);
        size_t size() const noexcept;
        double x0() const noexcept;
        double x1() const noexcept;
        double dx() const noexcept;
        double x(size_t i) const;
        const Vector& coordinates() const noexcept;
    private:
        double x0_;
        double x1_;
        double dx_;
        size_t nx_;
        Vector x_;
};