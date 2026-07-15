#include "core/Vector.h"
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

/* Size checking helper */
void Vector::checkSize(const Vector& rhs) const{
    if (size() != rhs.size()){
        throw std::invalid_argument("Vector sizes do not match.");
    }
}

/* Addition */
Vector Vector::operator+(const Vector& rhs) const {
    checkSize(rhs);
    Vector addition(size());
    for (std::size_t i = 0; i < size(); ++i){
        addition[i] = data_[i] + rhs[i];
    }
    
    return addition;
}

/* Subtraction */
Vector Vector::operator-(const Vector& rhs) const{
    checkSize(rhs);
    Vector subtraction(size());
    for (std::size_t i = 0; i < size(); ++i){
        subtraction[i] = data_[i] - rhs[i];
    }

    return subtraction;
}

/* Unary minus */
Vector Vector::operator-() const {
    Vector result(size());
    for (std::size_t i = 0; i < size(); ++i){
        result[i] = -data_[i];
    }

    return result;
}

/* Scalar multiplication */
Vector Vector::operator*(double scalar) const{
    Vector result(size());
    for (std::size_t i = 0; i < size(); ++i){
        result[i] = scalar * data_[i];
    }

    return result;
}

/* Scalar division */
Vector Vector::operator/(double scalar) const{
    Vector result(size());
    for (std::size_t i = 0; i < size(); ++i){
        result[i] = data_[i]/scalar;
    }

    return result;
}

/* Compound operators */
Vector& Vector::operator+=(const Vector& rhs){
    checkSize(rhs);

    for (std::size_t i = 0; i < size(); ++i){
        data_[i] += rhs[i];
    }

    return *this;
}

Vector& Vector::operator-=(const Vector& rhs){
    checkSize(rhs);

    for (std::size_t i = 0; i < size(); ++i){
        data_[i] -= rhs[i];
    }

    return *this;
}

Vector& Vector::operator*=(double scalar)
{
    for (double& value : data_)
        value *= scalar;

    return *this;
}

Vector& Vector::operator/=(double scalar)
{
    for (double& value : data_)
        value /= scalar;

    return *this;
}

/* Friend function */
Vector operator*(double scalar, const Vector& vec){
    return vec * scalar;
}

/* Dot product */
double Vector::dot(const Vector& rhs) const {
    checkSize(rhs);

    return std::inner_product(data_.begin(), data_.end(), rhs.data_.begin(), 0.0);
}

/* Comparison */
bool Vector::operator==(const Vector& rhs) const{
    return data_ == rhs.data_;
}

bool Vector::operator!=(const Vector& rhs) const{
    return !(*this == rhs);
}

/* Numerical Comparison */
bool Vector::isApprox(const Vector& rhs, double tol) const{
    checkSize(rhs);

    for (std::size_t i = 0; i < size(); ++i){
        const double a = data_[i];
        const double b = rhs[i];
        
        const double diff = std::abs(a - b);

        const double scale = std::max({1.0,std::abs(a),std::abs(b)});

        if (diff > tol * scale) return false;
    }

    return true;
}

bool Vector::isApproxNorm(const Vector& rhs, double tol) const{
    checkSize(rhs);

    Vector diff = *this - rhs;

    const double scale = std::max({1.0, this->normL2(), rhs.normL2()});

    return diff.normL2() <= tol * scale;
}

double Vector::maxAbsDifference(const Vector& rhs) const{
    checkSize(rhs);
    double error = 0.0;

    for (std::size_t i = 0; i < size(); ++i){
        error = std::max(error, std::abs(data_[i] - rhs[i]));
    }

    return error;
}
