#include "Vector.h"
#include <algorithm>    // std::fill, std::min_element, std::max_element
#include <numeric>      // std::sqrt, std::abs
#include <cmath>        // std::accumulate, std::inner_product
#include <stdexcept>    // std::runtime_error

/*
|----------------------------|
|-------- Constructors ------|
|----------------------------|
*/

Vector::Vector() = default;
Vector::Vector(std::size_t n) : data_(n, 0.0){}
Vector::Vector(size_t n, double value) : data_(n, value) {}
Vector::Vector(std::initializer_list<double> values) : data_(values) {}

/*
|----------------------------|
|-------- Capacity ----------|
|----------------------------|
*/

std::size_t Vector::size() const noexcept {
    return data_.size();
}

bool Vector::empty() const noexcept {
    return data_.empty();
}

void Vector::resize(std::size_t n){
    data_.resize(n);
}

/*
|----------------------------|
|-------- Element Access ----|
|----------------------------|
*/

double& Vector::operator[](size_t i){
    return data_[i];
}

const double& Vector::operator[](size_t i) const{
    return data_[i];
}

double& Vector::at(size_t i){
    return data_.at(i);
}

const double& Vector::at(size_t i) const{
    return data_.at(i);
}

/*
|----------------------------|
|-------- Utility functions -|
|----------------------------|
*/

void Vector::fill(double value){
    std::fill(data_.begin(), data_.end(), value);
}

/*
|----------------------------|
|--- Numerical Operations ---|
|----------------------------|
*/

double Vector::sum() const{
    return std::accumulate(data_.begin(), data_.end(), 0.0);
}

double Vector::normL2() const{
    double sum_sq = std::inner_product(data_.begin(), data_.end(), data_.begin(), 0.0);
    return std::sqrt(sum_sq);
}

double Vector::normInf() const{
    if (data_.empty()){
        throw std::runtime_error("normInf() called on an empty vector!");
    }
    double max_abs = 0.0;
    for (double value : data_){
        max_abs = std::max(max_abs, std::abs(value));
    }
    return max_abs;
}

double Vector::min() const{
    if (data_.empty()){
        throw std::runtime_error("min() called on an empty vector!");
    }
    return *std::min_element(data_.begin(), data_.end());
}

double Vector::max() const{
    if (data_.empty()){
        throw std::runtime_error("max() called on an empty vector!");
    }
    return *std::max_element(data_.begin(), data_.end());
}
