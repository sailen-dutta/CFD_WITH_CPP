#include "core/Grid1D.h"
#include <stdexcept>

Grid1D::Grid1D(double x0, double x1, size_t nx) : x0_(x0), x1_(x1), nx_(nx), x_(nx){
    if (nx < 2){
        throw std::invalid_argument("Grid1D: nx must be atleast 2.");
    }

    if (x1 <= x0){
        throw std::invalid_argument("Grid1D: x1 must be greater than x0.");
    }

    dx_ = (x1_ - x0_)/static_cast<double>(nx_ - 1);
    // x_.resize(nx_);
    for (size_t i = 0; i < nx_; ++i){
        x_[i] = x0_ + static_cast<double>(i) * dx_;
    }
}

size_t Grid1D::size() const noexcept{
    return nx_;
}

double Grid1D::x0() const noexcept {
    return x0_;
}

double Grid1D::x1() const noexcept {
    return x1_;
}

double Grid1D::dx() const noexcept {
    return dx_;
}

double Grid1D::x(size_t i) const {
    return x_.at(i);
}

const Vector& Grid1D::coordinates() const noexcept {
    return x_;
}