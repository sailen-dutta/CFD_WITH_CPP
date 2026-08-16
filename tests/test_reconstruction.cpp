#include "numerics/reconstruction/PiecewiseConstantReconstruction.h"
#include "core/Field1D.h"
#include "core/Grid1D.h"

#include <gtest/gtest.h>

TEST(PiecewiseConstantReconstructionTest, ConstantField){
    Grid1D grid(0.0, 1.0, 5);
    Field1D U(grid, 1);
    
    U.fill(3.0);

    PiecewiseConstantReconstruction reconstruction;

    Vector UL(1);
    Vector UR(1);

    reconstruction.reconstruct(U, 2, UL, UR);

    EXPECT_DOUBLE_EQ(UL[0], 3.0);
    EXPECT_DOUBLE_EQ(UR[0], 3.0);
}

TEST(PiecwiseReconstructionTest, UsesAdjacentCellValues){
    Grid1D grid(0.0, 1.0, 5);
    Field1D U(grid, 1);

    U[0][0] = 1.0;
    U[1][0] = 2.0;
    U[2][0] = 4.0;
    U[3][0] = 8.0;
    U[4][0] = 16.0;

    Vector UL(1);
    Vector UR(1);

    PiecewiseConstantReconstruction reconstruction;

    /* Interface 2 is between cell 2 and cell 3 */
    reconstruction.reconstruct(U, 2, UL, UR);

    EXPECT_DOUBLE_EQ(UL[0], 4.0);
    EXPECT_DOUBLE_EQ(UR[0], 8.0);
}

TEST(PiecewiseReconstructionTest, PeriodicBC){
    Grid1D grid(0.0, 1.0, 5);
    Field1D U(grid, 1);

    U[0][0] = 1.0;
    U[1][0] = 2.0;
    U[2][0] = 3.0;
    U[3][0] = 4.0;
    U[4][0] = 5.0;

    Vector UL(1);
    Vector UR(1);

    PiecewiseConstantReconstruction reconstruction;

    /* Interface 4 is between cell 4 and cell 0 */
    reconstruction.reconstruct(U, 4, UL, UR);

    EXPECT_DOUBLE_EQ(UL[0], 5.0);
    EXPECT_DOUBLE_EQ(UR[0], 1.0);
}