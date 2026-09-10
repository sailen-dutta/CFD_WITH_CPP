#include "numerics/time/SSPRK3.h"
#include "numerics/spatial/SpatialOperator.h"
#include "core/Field1D.h"
#include "core/Grid1D.h"
#include "core/Vector.h"
#include <gtest/gtest.h>

class ConstantRHSOperator : public SpatialOperator {
    public:
        explicit ConstantRHSOperator(const Vector& rhs) : rhs_(rhs) {}
        void computeRHS(const Field1D& u, Field1D& rhs) const override{
            ASSERT_EQ(rhs.numVariables(), rhs_.size());
            for (std::size_t i = 0; i < u.size(); ++i) {
                rhs[i] = rhs_;
            }
        }
    private:
        Vector rhs_;
};

class IdentityOperator : public SpatialOperator {
public:

    void computeRHS(const Field1D& u, Field1D& rhs) const override
    {
        for (std::size_t i = 0; i < u.size(); ++i) {
            rhs[i] = u[i];
        }
    }
};

TEST(SSPRK3Test, UpdatesStateUsingConstantRHS)
{
    Grid1D grid(0.0, 1.0, 3);
    Field1D u(grid, 1);

    for (std::size_t i = 0; i < u.size(); ++i) {
        u[i][0] = 1.0;
    }

    Vector rhs_value(1);
    rhs_value[0] = 2.0;

    ConstantRHSOperator op(rhs_value);
    SSPRK3 integrator;

    const double dt = 0.1;

    integrator.advance(u, op, dt);

    /* For a constant RHS, SSPRK3 reduces to:
     u_new = u_old + dt * RHS
           = 1.0 + 0.1 * 2.0
           = 1.2
    */

    for (std::size_t i = 0; i < u.size(); ++i) {
        EXPECT_DOUBLE_EQ(u[i][0], 1.2);
    }
}

TEST(SSPRK3Test, ZeroRHSLeavesStateUnchanged)
{
    Grid1D grid(0.0, 1.0, 3);
    Field1D u(grid, 1);

    for (std::size_t i = 0; i < u.size(); ++i) {
        u[i][0] = static_cast<double>(i + 1);
    }

    Field1D original = u;

    Vector rhs_value(1);
    rhs_value[0] = 0.0;

    ConstantRHSOperator op(rhs_value);
    SSPRK3 integrator;

    integrator.advance(u, op, 0.1);

    for (std::size_t i = 0; i < u.size(); ++i) {
        EXPECT_DOUBLE_EQ(u[i][0], original[i][0]);
    }
}

TEST(SSPRK3Test, UpdatesAllVariables)
{
    Grid1D grid(0.0, 1.0, 2);
    Field1D u(grid, 3);

    for (std::size_t i = 0; i < u.size(); ++i) {
        u[i][0] = 1.0;
        u[i][1] = 2.0;
        u[i][2] = 3.0;
    }

    Vector rhs_value(3);
    rhs_value[0] = 10.0;
    rhs_value[1] = -2.0;
    rhs_value[2] = 0.5;

    ConstantRHSOperator op(rhs_value);
    SSPRK3 integrator;

    const double dt = 0.1;

    integrator.advance(u, op, dt);

    EXPECT_DOUBLE_EQ(u[0][0], 2.0);
    EXPECT_DOUBLE_EQ(u[0][1], 1.8);
    EXPECT_DOUBLE_EQ(u[0][2], 3.05);

    EXPECT_DOUBLE_EQ(u[1][0], 2.0);
    EXPECT_DOUBLE_EQ(u[1][1], 1.8);
    EXPECT_DOUBLE_EQ(u[1][2], 3.05);
}

TEST(SSPRK3Test, PerformsThreeStageEvaluation)
{
    Grid1D grid(0.0, 1.0, 2);
    Field1D u(grid, 1);

    u[0][0] = 1.0;
    u[1][0] = 1.0;

    IdentityOperator op;
    SSPRK3 integrator;

    const double dt = 0.1;

    integrator.advance(u, op, dt);

    /* du/dt = u
    
     Stage 1:
     rhs1 = 1.0
     u1   = 1.1
    
     Stage 2:
     rhs2 = 1.1
     u2   = 1.0525
    
     Stage 3:
     rhs3 = 1.0525
    
     u_new = 1.1051666666666666
    */
    EXPECT_DOUBLE_EQ(u[0][0], 1.1051666666666667);
    EXPECT_DOUBLE_EQ(u[1][0], 1.1051666666666667);
}
