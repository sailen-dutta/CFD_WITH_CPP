#include "analysis/ErrorAnalysis.h"
#include "core/Field1D.h"
#include "core/Grid1D.h"

#include <gtest/gtest.h>
#include <cmath>

TEST(ErrorAnalysisTest, ZeroError){
    Grid1D grid(0.0,1.0,5);
    
    Field1D numerical(grid);
    Field1D exact(grid);

    numerical.fill(1.0);
    exact.fill(1.0);

    EXPECT_DOUBLE_EQ(ErrorAnalysis::computeL2Error(numerical, exact), 0.0);

    EXPECT_DOUBLE_EQ(ErrorAnalysis::computeLinfError(numerical,exact),0.0);
}

TEST(ErrorAnalysisTest, ConstantUnitError){
    Grid1D grid(0.0, 1.0, 5);

    Field1D numerical(grid);
    Field1D exact(grid);

    numerical.fill(1.0);
    exact.fill(0.0);

    EXPECT_DOUBLE_EQ(ErrorAnalysis::computeL2Error(numerical, exact), 1.0);
    
    EXPECT_DOUBLE_EQ(ErrorAnalysis::computeLinfError(numerical, exact), 1.0);
}

TEST(ErrorAnalysisTest, L2LinfThrowsOnSizeMismatch){
    Grid1D grid1(0.0, 1.0, 5);
    Grid1D grid2(0.0, 1.0, 7);

    Field1D u1(grid1);
    Field1D u2(grid2);

    EXPECT_THROW(ErrorAnalysis::computeL2Error(u1,u2), std::runtime_error);
    EXPECT_THROW(ErrorAnalysis::computeLinfError(u1,u2), std::runtime_error);
}

TEST(ErrorAnalysis, KnownL2Value){
    Grid1D grid(0.0, 1.0, 3);

    Field1D numerical(grid), exact(grid);

    numerical[0] = 1.0;
    numerical[1] = 2.0;
    numerical[2] = 3.0;

    exact.fill(0.0);

    double expected = std::sqrt(14.0/3.0);

    EXPECT_NEAR(ErrorAnalysis::computeL2Error(numerical, exact), expected, 1e-12);
}

TEST(ErrorAnalysisTest, SymmetryProperty)
{
    Grid1D grid(0.0, 1.0, 5);

    Field1D u(grid);
    Field1D v(grid);

    u[0] = 1.0;
    u[1] = 2.0;
    u[2] = 3.0;
    u[3] = 4.0;
    u[4] = 5.0;

    v.fill(0.0);

    double l2_uv = ErrorAnalysis::computeL2Error(u,v);

    double l2_vu = ErrorAnalysis::computeL2Error(v,u);

    double linf_uv = ErrorAnalysis::computeLinfError(u,v);

    double linf_vu = ErrorAnalysis::computeLinfError(v,u);

    EXPECT_DOUBLE_EQ(l2_uv,l2_vu);

    EXPECT_DOUBLE_EQ(linf_uv,linf_vu);
}

TEST(ErrorAnalysisTest, NormsAreNonNegative)
{
    Grid1D grid(0.0, 1.0, 5);

    Field1D u(grid);
    Field1D v(grid);

    u[0] = -1.0;
    u[1] =  2.0;
    u[2] = -3.0;
    u[3] =  4.0;
    u[4] = -5.0;

    v.fill(0.0);

    double l2 = ErrorAnalysis::computeL2Error(u,v);

    double linf = ErrorAnalysis::computeLinfError(u,v);

    EXPECT_GE(l2,0.0);

    EXPECT_GE(linf,0.0);
}

TEST(ErrorAnalysisTest, LinfReturnsMaximumError)
{
    Grid1D grid(0.0, 1.0, 5);

    Field1D numerical(grid);
    Field1D exact(grid);

    exact.fill(0.0);

    numerical[0] = 0.1;
    numerical[1] = 0.7;
    numerical[2] = 0.3;
    numerical[3] = 0.2;
    numerical[4] = 0.5;

    double linf = ErrorAnalysis::computeLinfError(numerical,exact);

    EXPECT_DOUBLE_EQ(linf, 0.7);
}









