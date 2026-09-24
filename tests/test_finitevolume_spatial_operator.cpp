#include "numerics/spatial/FiniteVolumeSpatialOperator.h"
#include "numerics/flux/RusanovFlux.h"
#include "numerics/reconstruction/PiecewiseConstantReconstruction.h"
#include "physics/equations/BurgersEquation.h"
#include "numerics/boundary/PeriodicBC.h"
#include "core/Field1D.h"
#include "core/Grid1D.h"
#include <gtest/gtest.h>

TEST(FiniteVolumeSpatialOperatorTest, ConstantFieldHasZeroRHS){
    /* A constant solution should remain constant 
       Since every cell contains the same value, flux entering a cell = flux leaving it
       Hence, RHS = -(F_right - F_left)/dx = 0 */
    Grid1D grid(0.0, 1.0, 11);
    BurgersEquation equation;
    RusanovFlux flux;
    PiecewiseConstantReconstruction reconstruction;
    Field1D U(grid, equation.numVariables(), 1);
    Field1D rhs(grid, equation.numVariables(), 1);

    U.fill(2.0);
    rhs.fill(0.0);


    FiniteVolumeSpatialOperator spatialOperator(equation, flux, reconstruction);

    spatialOperator.computeRHS(U, rhs);

    for (std::size_t i = 0; i < U.size(); ++i){
        EXPECT_DOUBLE_EQ(rhs[i][0], 0.0);
    }
}

TEST(FiniteVolumeSpatialOperator, NonConstantBurgersField){
    /*
        Test the finite-volume spatial discretization for
        a non-constant Burgers solution.

        Burgers equation:

            U_t + F(U)_x = 0

        with

            F(U) = U^2 / 2.

        The spatial operator computes

            RHS_i = -(Fhat_{i+1/2} - Fhat_{i-1/2}) / dx.

        We use:
            - piecewise-constant reconstruction
            - Rusanov numerical flux
            - periodic boundaries
    */
   Grid1D grid(0.0, 1.0, 5);

   BurgersEquation equation;
   RusanovFlux flux;
   PiecewiseConstantReconstruction reconstruction;

   Field1D u(grid, equation.numVariables(), 1);
   Field1D rhs(grid, equation.numVariables(), 1);

   /* Non-constant periodic field: U = [1, 2, 3, 4, 5] */
   u[1][0] = 1.0;
   u[2][0] = 2.0;
   u[3][0] = 3.0;
   u[4][0] = 4.0;
   u[5][0] = 5.0;

   PeriodicBC boundary;
   boundary.apply(u);

   rhs.fill(0.0);


   FiniteVolumeSpatialOperator spatial_operator(equation, flux, reconstruction);

   spatial_operator.computeRHS(u, rhs);

   /* For dx = 0.25, the expected RHS is: [ 65, -6, -10, -14, -35 ]

    The first cell includes the periodic interface between U[4] = 5 and U[0] = 1. */
    const double expected[] = {65.0, -6.0, -10.0, -14.0, -35.0};

    for (std::size_t i = 0; i < u.numPhysicalCells(); ++i){
	const std::size_t si = u.physicalIndex(i);
        EXPECT_NEAR(rhs[si][0], expected[i], 1e-12);
    }
}

TEST(FiniteVolumeSpatialOperator, ConstantFieldWithPeriodicBCProducesZeroRHS) {
	Grid1D grid(0.0, 1.0, 5);

	BurgersEquation equation;
	RusanovFlux flux;
	PiecewiseConstantReconstruction reconstruction;

	FiniteVolumeSpatialOperator op(equation, flux, reconstruction);

	Field1D U(grid, equation.numVariables(), 1);
	Field1D rhs(grid, equation.numVariables(), 1);

	/* G | C0 | C1 | C2 | C3 | C4 | G */
	U[1][0] = 3.0;
	U[2][0] = 3.0;
	U[3][0] = 3.0;
	U[4][0] = 3.0;
	U[5][0] = 3.0;

	PeriodicBC boundary;
	boundary.apply(U);

	rhs.fill(123.0);

	op.computeRHS(U, rhs);

	/* All physical cells RHS values should be zero */
	for (std::size_t i = 0; i < U.numPhysicalCells(); ++i) {
		const std::size_t si = U.physicalIndex(i);

		EXPECT_DOUBLE_EQ(rhs[si][0], 0.0);
	}

	/* Ghost cell values should not be modified */
	EXPECT_DOUBLE_EQ(rhs[0][0], 123.0);
	EXPECT_DOUBLE_EQ(rhs[6][0], 123.0);
}

TEST(FiniteVolumeSpatialOperator, SingleNonZeroValueProducesExpectedRHS) {
	Grid1D grid(0.0, 1.0, 5);

	BurgersEquation equation;
	RusanovFlux flux;
	PiecewiseConstantReconstruction reconstruction;

	FiniteVolumeSpatialOperator op(equation, flux, reconstruction);

	Field1D U(grid, equation.numVariables(), 1);
	Field1D rhs(grid, equation.numVariables(), 1);

	/* G | C0 | C1 | C2 | C3 | C4 | G */
	/* U in C1 = 1, rest all are zero */
	U[1][0] = U[3][0] = U[4][0] = U[5][0] = 0.0;
	U[2][0] = 1.0;

	PeriodicBC boundary;
	boundary.apply(U);

	rhs.fill(0.0);

	op.computeRHS(U, rhs);

	std::vector<double> expectedRHS = {1, -4, 3, 0, 0};

	for (std::size_t i = 0; i < U.numPhysicalCells(); ++i){
		const std::size_t si = U.physicalIndex(i);
		EXPECT_DOUBLE_EQ(rhs[si][0], expectedRHS[i]);
	}
}

