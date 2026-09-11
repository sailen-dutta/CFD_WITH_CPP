#include "physics/equations/EulerEquation.h"
#include "core/Vector.h"
#include <cmath>
#include <gtest/gtest.h>

TEST(EulerEquationTest, DefaultGamma) {
	EulerEquation equation;
	EXPECT_DOUBLE_EQ(equation.gamma(), 1.4);
}

TEST(EulerEquationTest, CustomGamma) {
	EulerEquation equation(1.67);
	EXPECT_DOUBLE_EQ(equation.gamma(), 1.67);
}


TEST(EulerEquationTest, LeftSodStateFlux) {
	EulerEquation equation;
	/* Use left sod state (rho, u, p) = (1, 0, 1)
	   Convert to conserved variables: E = p/(gamma - 1) + 1/2 * (rho * u * u) = 1/0.4 = 2.5
	   Physical flux = [0, 1, 0]
	*/
	Vector U = {1.0, 0.0, 2.5};
	
	Vector F = equation.flux(U);

	EXPECT_DOUBLE_EQ(F[0], 0.0);
	EXPECT_DOUBLE_EQ(F[1], 1.0);
	EXPECT_DOUBLE_EQ(F[2], 0.0);
}

TEST(EulerEquationTest, LeftSodStateWaveSpeed) {
	EulerEquation equation;

	Vector U = {1.0, 0.0, 2.5};
	
	const double a = std::sqrt(equation.gamma() * 1/ U[0]);	/* a = sqrt(gamma*p/rho) */	
	EXPECT_DOUBLE_EQ(equation.maxWaveSpeed(U), a);
}

TEST(EulerEquationTest, HasThreeVariables) {
	EulerEquation equation;

	EXPECT_EQ(equation.numVariables(), 3);
}

TEST(EulerEquationTest, RightSodStateFlux) {
	EulerEquation equation;

	/* Use right sod state (rho, u, p) = (0.125, 0, 0.1)
	   E = p/(gamma - 1) + 1/2 * (rho * u * u) = 0.1/0.4 = 0.25
	   Physical flux = [0, 0.1, 0]
	*/
	Vector U = {0.125, 0, 0.25};

	Vector F = equation.flux(U);

	EXPECT_DOUBLE_EQ(F[0], 0.0);
	EXPECT_DOUBLE_EQ(F[1], 0.1);
	EXPECT_DOUBLE_EQ(F[2], 0.0);
}

TEST(EulerEquationTest, RightSodStateWaveSpeed) {
	EulerEquation equation;

	Vector U = {0.125, 0, 0.25};

	const double a = std::sqrt(equation.gamma() * 0.1 / 0.125);

	EXPECT_DOUBLE_EQ(equation.maxWaveSpeed(U), a);
}
