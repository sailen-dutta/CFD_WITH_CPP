#include "physics/initial_conditions/InitialConditions.h"

/* Burgers' equation has a single conserved variable.
   Store the initial condition in the first (and only) component
   of the conserved variable vector. */
void InitialConditions::squarePulse(Field1D& field, double x_start, double x_end, double value){
    field.fill(0.0);
    for (size_t i = 0; i < field.size(); ++i){
        double x = field.grid().x(i);
        if (x >= x_start && x <= x_end){
            field[i][0] = value;
        }
    }
}

void InitialConditions::gaussian(Field1D& field, double center, double sigma){
    field.fill(0.0);
    for (size_t i = 0; i < field.size(); ++i){
        double x = field.grid().x(i);
        double exponent = -((x - center) * (x - center))/(2.0 * sigma * sigma);
        field[i][0] = std::exp(exponent);
    }
}

void InitialConditions::sinewave(Field1D& field){
    field.fill(0.0);
    constexpr double pi = std::numbers::pi;
    for (size_t i = 0; i < field.size(); ++i){
        double x = field.grid().x(i);
        field[i][0] = std::sin(4 * pi * x);
    }
}

void InitialConditions::sodShockTube(Field1D& field, double x_discontinuity, double gamma) {
	field.fill(0.0);

	const double rho_left = 1.0;
	const double u_left   = 0.0;
	const double p_left   = 1.0;

	const double rho_right = 0.125;
	const double u_right   = 0.0;
	const double p_right   = 0.1;

	const double E_left  = p_left / (gamma - 1.0) + 0.5 * rho_left * u_left * u_left;
	const double E_right = p_right / (gamma - 1.0) + 0.5 * rho_right * u_right * u_right;

	for (std::size_t i = 0; i < field.size(); ++i) {
		const double x = field.grid().x(i);

		if (x < x_discontinuity) {
			field[i][0] = rho_left;
			field[i][1] = rho_left * u_left;
			field[i][2] = E_left;
		}
		else {
			field[i][0] = rho_right;
			field[i][1] = rho_right * u_right;
			field[i][2] = E_right;
		}
	}
}

