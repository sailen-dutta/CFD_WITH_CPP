#include "Field1D.h"

Field1D::Field1D(const Grid1D& grid):grid_(grid), values_(grid.size()) {}

size_t Field1D::size() const noexcept {
    return values_.size();
}

double& Field1D::operator[](size_t i){
    return values_[i];
}

const double& Field1D::operator[](size_t i) const {
    return values_[i];
}

double Field1D::at(size_t i) const{
    return values_.at(i);
}

void Field1D::fill(double value){
    values_.fill(value);
}

const Grid1D& Field1D::grid() const{
    return grid_;
}

const Vector& Field1D::values() const{
    return values_;
}