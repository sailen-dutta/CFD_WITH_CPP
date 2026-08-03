#pragma once

#include<cstddef>
#include<initializer_list>
#include<vector>

class Vector{
    public:
        /* Constructors */    
        Vector();
        explicit Vector(std::size_t n);
        Vector(std::size_t n, double value);
        Vector(std::initializer_list<double> values);

        /* Capacity */
        [[nodiscard]] std::size_t size() const noexcept;
        [[nodiscard]] bool empty() const noexcept;
        void resize(std::size_t n);

        /* Element Access */
        double& operator[](std::size_t i);
        const double& operator[](std::size_t i) const;

        double& at(std::size_t i);
        const double& at(std::size_t i) const;

        /* Utilities */
        void fill(double value);

        /* Arithmetic */
        [[nodiscard]] Vector operator+(const Vector& rhs) const;
        [[nodiscard]] Vector operator-(const Vector& rhs) const;
        [[nodiscard]] Vector operator-() const;
        [[nodiscard]] Vector operator*(double scalar) const;
        [[nodiscard]] Vector operator/(double scalar) const;
        Vector& operator+=(const Vector& rhs);
        Vector& operator-=(const Vector& rhs);
        Vector& operator*=(double scalar);
        Vector& operator/=(double scalar);

        friend Vector operator*(double scalar, const Vector& vec);

        /* Numerical operations */
        [[nodiscard]] double dot(const Vector& rhs) const;
        [[nodiscard]] double sum() const;
        [[nodiscard]] double normL2() const;
        [[nodiscard]] double normInf() const;
        double min() const;
        double max() const;

        /* Comparisons */
        bool operator==(const Vector& rhs) const;
        bool operator!=(const Vector& rhs) const;

        /* Numerical Comparison */
        bool isApprox(const Vector& rhs, double tol = 1e-12) const;
        bool isApproxNorm(const Vector& rhs, double tol = 1e-12) const;
        double maxAbsDifference(const Vector& rhs) const;
        
        auto begin() noexcept {return data_.begin();}
        auto end() noexcept {return data_.end();}
        auto begin() const noexcept {return data_.begin();}
        auto end() const noexcept {return data_.end();}
    
    private:
        std::vector<double> data_;
        void checkSize(const Vector& rhs) const;

};