#include "physics/equations/EulerEquation.h"
#include <cmath>

EulerEquation::EulerEquation(double gamma) : gamma_(gamma) {}

Vector EulerEquation::flux(const Vector& U) const {
	Vector F(numVariables());
	const double rho = U[0];
	const double momentum = U[1];
	const double E = U[2];

	const double u = U[1] / U[0];

	const double p = (gamma_ - 1.0) * (E - 0.5 * rho * u * u);

	F[0] = momentum;
	F[1] = momentum * u + p;
	F[2] = u * (E + p);

	return F;
}

double EulerEquation::maxWaveSpeed(const Vector& U) const {
	
	const double rho = U[0];
	const double momentum = U[1];
	const double E = U[2];

	const double u = momentum / rho;

	const double p = (gamma_ - 1.0) * (E - 0.5 * rho * u * u);

	const double a = std::sqrt(gamma_ * p / rho);

	return (std::abs(u) + a);
}

double EulerEquation::gamma() const {
	return gamma_;
}

std::size_t EulerEquation::numVariables() const {
	return 3;
}





