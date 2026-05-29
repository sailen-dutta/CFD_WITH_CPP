#pragma once

#include<cstddef>
#include<initializer_list>
#include<vector>

class Vector{
    public:
        Vector();
        explicit Vector(std::size_t n);
        Vector(std::size_t n, double value);
        Vector(std::initializer_list<double> values);

        std::size_t size() const noexcept;
        bool empty() const noexcept;
        void resize(std::size_t n);

        double& operator[](std::size_t i);
        const double& operator[](std::size_t i) const;

        double& at(std::size_t i);
        const double& at(std::size_t i) const;

        void fill(double value);

        double sum() const;
        double normL2() const;
        double normInf() const;
        double min() const;
        double max() const;

        auto begin() noexcept {return data_.begin();}
        auto end() noexcept {return data_.end();}
        auto begin() const noexcept {return data_.begin();}
        auto end() const noexcept {return data_.end();}
    
    private:
        std::vector<double> data_;

};