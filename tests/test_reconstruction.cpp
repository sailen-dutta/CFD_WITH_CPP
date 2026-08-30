#include "numerics/reconstruction/PiecewiseConstantReconstruction.h"
#include "numerics/reconstruction/MUSCLReconstruction.h"
#include "numerics/limiter/UnlimitedLimiter.h"
#include "numerics/reconstruction/ReconstructionFactory.h"
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

TEST(MUSCLReconstructionTest, ConstantField){
    Grid1D grid(0.0, 1.0, 5);
    Field1D U(grid, 1);

    U.fill(3.0);

    UnlimitedLimiter limiter;
    MUSCLReconstruction reconstruction(limiter);

    Vector UL(1);
    Vector UR(1);

    reconstruction.reconstruct(U,2,UL,UR);

    EXPECT_DOUBLE_EQ(UL[0], 3.0);
    EXPECT_DOUBLE_EQ(UR[0], 3.0);
}

TEST(MUSLReconstructionTest, LinearField){
    Grid1D grid(0.0, 1.0, 5);
    Field1D U(grid, 1);

    U[0][0] = 1.0;
    U[1][0] = 2.0;
    U[2][0] = 3.0;
    U[3][0] = 4.0;
    U[4][0] = 5.0;

    UnlimitedLimiter limiter;
    MUSCLReconstruction reconstruction(limiter);

    Vector UL(1);
    Vector UR(1);

    /* Interface 2 is between cell 2 and cell 3 */
    reconstruction.reconstruct(U, 2, UL, UR);

    EXPECT_DOUBLE_EQ(UL[0], 3.5);
    EXPECT_DOUBLE_EQ(UR[0], 3.5);
}

TEST(MUSCLReconstructionTest, MultipleVariables){
    Grid1D grid(0.0, 1.0, 5);
    Field1D U(grid, 2);

    /* Variable 0: [1,2,3,4,5]
       Variable 1: [10, 20, 30, 40, 50] */

    for (std::size_t i = 0; i < U.size(); i++){
        U[i][0] = static_cast<double>(i+1);
        U[i][1] = 10.0 * static_cast<double>(i+1);
    }

    UnlimitedLimiter limiter;
    MUSCLReconstruction reconstruction(limiter);

    Vector UL(2);
    Vector UR(2);

    reconstruction.reconstruct(U, 2, UL, UR);

    EXPECT_DOUBLE_EQ(UL[0], 3.5);
    EXPECT_DOUBLE_EQ(UR[0], 3.5);

    EXPECT_DOUBLE_EQ(UL[1], 35.0);
    EXPECT_DOUBLE_EQ(UR[1], 35.0);
}

TEST(MUSCLReconstructionTest, PeriodicInterface){
    Grid1D grid(0.0, 1.0, 5);
    Field1D U(grid, 1);

    /* Cell: 0  1   2   3   4
       U   : 1  2   3   4   5
       
       We reconstruct interface 4 which is between cell 4 and cell 0
       cell 4 | cell 0
       U    5 |      1 
       
       Because reconstruction is periodic, the neighbours of cell 4 and cell 0 must wrap around */
    U[0][0] = 1.0;
    U[1][0] = 2.0;
    U[2][0] = 3.0;
    U[3][0] = 4.0;
    U[4][0] = 5.0;

    UnlimitedLimiter limiter;
    MUSCLReconstruction reconstruction(limiter);

    Vector UL(1);
    Vector UR(1);

    reconstruction.reconstruct(U, 4, UL, UR);

    /* For cell 4:
        left difference = U[4] - U[3]
                        = 5 - 4 = 1
        
        right difference = U[0] - U[4]
                         = 1 - 5 = -4
                         
        slope_4 = 0.5*(1 + (-4))
                = -1.5
        
        Therefore, UL = 5 + 0.5(-1.5) = 4.25
        
       For cell 0:
        left difference = U[0] - U[4]
                        = 1 - 5 = -4
        
        right difference = U[1] - U[0] 
                         = 2 - 1 = 1
        
        slope_0 = 0.5*(-4 + 1) = -1.5
        
        Therefore UR = 1 - 0.5(-1.5) = 1.75 */
    EXPECT_DOUBLE_EQ(UL[0], 4.25);
    EXPECT_DOUBLE_EQ(UR[0], 1.75);
}

/* Reconstruction Factory tests. ReconstructionFactory requires SlopeLimiter&. We will use Unlimited limiter to satisfy the dependecy */
TEST(ReconstructionFactoryTest, CreatesPiecewiseConstant){
    UnlimitedLimiter limiter;

    /* Factory should create PiecewiseConstantReconstruction when given the string piecewise_constant */
    auto reconstruction = ReconstructionFactory::create("piecewise_constant", limiter);

    /* The factory returns a unique_ptr<Reconstruction>, so verify that an object was actually created */
    ASSERT_NE(reconstruction, nullptr);

    /* Check that the oject is specifically PiecewiseConstantReconstruction */
    EXPECT_NE(dynamic_cast<PiecewiseConstantReconstruction*>(reconstruction.get()), nullptr);
}

TEST(ReconstructionFactoryTest, CreatesMUSCL){
    UnlimitedLimiter limiter;
    auto reconstruction = ReconstructionFactory::create("muscl", limiter);
    ASSERT_NE(reconstruction, nullptr);
    EXPECT_NE(dynamic_cast<MUSCLReconstruction*>(reconstruction.get()), nullptr);
}

TEST(ReconstructionFactoryTest, UnknownReconstructionThrows){
    UnlimitedLimiter limiter;
    EXPECT_THROW(ReconstructionFactory::create("unknown", limiter), std::runtime_error);
}