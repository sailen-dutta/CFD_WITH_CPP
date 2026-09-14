#include "numerics/boundary/PeriodicBC.h"
#include "core/Field1D.h"
#include "core/Grid1D.h"
#include <gtest/gtest.h>

TEST(PeriodicBCTest, OneGhostCell) {
	Grid1D grid(0.0, 1.0, 5);
	Field1D field(grid, 1, 1);

	/* index: 0	1	2	3	4	5	6
	 	  G	C0	C1	C2	C3	C4	G
	   
   	   Values:
	   	  C0 = 10
		  C1 = 20
		  C2 = 30
		  C3 = 40
		  C4 = 50
        */
	field[1][0] = 10.0;
	field[2][0] = 20.0;
	field[3][0] = 30.0;
	field[4][0] = 40.0;
	field[5][0] = 50.0;

	PeriodicBC boundary;
	boundary.apply(field);

	/* Left ghost gets the rightmost physical cell value */
	EXPECT_DOUBLE_EQ(field[0][0], 50.0);
	/* Right ghost gets the leftmost physical cell value */
	EXPECT_DOUBLE_EQ(field[6][0], 10.0);
}

TEST(PeriodicBCTest, TwoGhostCells) {
	Grid1D grid(0.0, 1.0, 5);
	Field1D field(grid, 1, 2);


	/* index: 0	1	2	3	4	5	6	7	8
	 	  G1	G2	C0	C1	C2	C3	C4	G3	G4

   	   Values:
	   	  C0 = 10
		  C1 = 20
		  C2 = 30
		  C3 = 40
		  C4 = 50
        */

	field[2][0] = 10.0;
	field[3][0] = 20.0;
	field[4][0] = 30.0;
	field[5][0] = 40.0;
	field[6][0] = 50.0;

	PeriodicBC boundary;
	boundary.apply(field);

	EXPECT_DOUBLE_EQ(field[0][0], 40.0);
	EXPECT_DOUBLE_EQ(field[1][0], 50.0);
	EXPECT_DOUBLE_EQ(field[7][0], 10.0);
	EXPECT_DOUBLE_EQ(field[8][0], 20.0);
}

TEST(PeriodicBCTest, CopiesAllVariables) {
	Grid1D grid(0.0, 1.0, 3);
	Field1D field(grid, 3, 1);

	/* C0 = [1,2,3] */
	field[1][0] = 1.0;
	field[1][1] = 2.0;
	field[1][2] = 3.0;

	/* C1 = [4,5,6] */
	field[2][0] = 4.0;
	field[2][1] = 5.0;
	field[2][2] = 6.0;

	/* C2 = [7,8,9] */
	field[3][0] = 7.0;
	field[3][1] = 8.0;
	field[3][2] = 9.0;

	PeriodicBC boundary;
	boundary.apply(field);
	
	EXPECT_DOUBLE_EQ(field[0][0], 7.0);
	EXPECT_DOUBLE_EQ(field[0][1], 8.0);
	EXPECT_DOUBLE_EQ(field[0][2], 9.0);

	EXPECT_DOUBLE_EQ(field[4][0], 1.0);
	EXPECT_DOUBLE_EQ(field[4][1], 2.0);
	EXPECT_DOUBLE_EQ(field[4][2], 3.0);
}

TEST(PeriodicBCTest, NoGhostCells) {
	Grid1D grid(0.0, 1.0, 5);
	Field1D field(grid, 1, 0);

	for (std::size_t i = 0; i < field.size(); ++i) {
		field[i][0] = static_cast<double>(i+1);
	}

	PeriodicBC boundary;
	boundary.apply(field);

	for (std::size_t i = 0; i < field.size(); ++i) {
		EXPECT_DOUBLE_EQ(field[i][0], static_cast<double>(i+1));
	}
}


