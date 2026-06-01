#include "analysis/ErrorAnalysis.h"
#include <cmath>
#include <stdexcept>

namespace ErrorAnalysis{
    double computeL2Error(const Field1D& numerical, const Field1D& exact){
        if (numerical.size() != exact.size()){
            throw std::runtime_error("L2 error: Size mismatch between exact and numerical solution.");
        }

        double sum = 0.0;

        for (size_t i = 0; i < numerical.size(); i++){
            double error = numerical[i] - exact[i];
            sum += error * error;
        }
        return std::sqrt(sum / static_cast<double> (numerical.size()));
    }

    double computeLinfError(const Field1D& numerical, const Field1D& exact){
        if (numerical.size() != exact.size()){
            throw std::runtime_error("L_inf error: Size mismatch between exact and numerical solution.");
        }
        double max_error = 0.0;
        for (size_t i = 0; i < numerical.size(); i++){
            double error = std::abs(numerical[i] - exact[i]);
            if (error > max_error) max_error = error;
        }
        return max_error;
    }
}