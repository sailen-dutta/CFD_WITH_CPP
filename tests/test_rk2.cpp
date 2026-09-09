#include "numerics/time/RK2.h"
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
        void computeRHS(const Field1D& u, Field1D& rhs) const override {
            for (std::size_t i = 0; i < u.size(); ++i){
                rhs[i] = u[i];
            }
        }
};

TEST(RK2Test, UpdatesUsingConstantRHS){
    Grid1D grid(0.0, 1.0, 3);
    Field1D u(grid, 1);

    for (std::size_t i = 0; i < u.size(); ++i){
        u[i][0] = 1.0;
    }

    Vector rhs_value(1);
    rhs_value[0] = 2.0;

    ConstantRHSOperator op(rhs_value);
    RK2 integrator;

    const double dt = 0.1;

    integrator.advance(u, op, dt);

    /* Constant RHS:    
     u_new = u_old + dt * RHS
           = 1.0 + 0.1 * 2.0 = 1.2 */
    for (std::size_t i = 0; i < u.size(); ++i){
        EXPECT_DOUBLE_EQ(u[i][0], 1.2);
    }
}

TEST(RK2Test, ZeroRHSLeavesStateUnchanged){
    Grid1D grid(0.0, 1.0, 3);
    Field1D u(grid, 1);

    for (std::size_t i = 0; i < u.size(); ++i){
        u[i][0] = static_cast<double>(i+1);
    }

    Field1D original = u;

    Vector rhs_value(1);
    rhs_value[0] = 0.0;

    ConstantRHSOperator op(rhs_value);
    RK2 integrator;

    const double dt = 0.1;

    integrator.advance(u, op, dt);

    for (std::size_t i = 0; i < u.size(); ++i){
        EXPECT_DOUBLE_EQ(u[i][0], original[i][0]);
    }
}

TEST(RK2Test, UpdatesAllVariables){
    Grid1D grid(0.0, 1.0, 3);
    Field1D u(grid, 3);

    for (std::size_t i = 0; i < u.size(); ++i){
        u[i][0] = 1.0;
        u[i][1] = 2.0;
        u[i][2] = 3.0;
    }

    Vector rhs_value = {10.0, -2.0, 0.5};

    ConstantRHSOperator op(rhs_value);
    RK2 integrator;

    const double dt = 0.1;

    integrator.advance(u, op, dt);

    for (std::size_t i = 0; i < u.size(); ++i){
        EXPECT_DOUBLE_EQ(u[i][0], 2.0);
        EXPECT_DOUBLE_EQ(u[i][1], 1.8);
        EXPECT_DOUBLE_EQ(u[i][2], 3.05);
    }
}

TEST(RK2Test, PerformsSecondStageOperation){
    Grid1D grid(0.0, 1.0, 2);
    Field1D u(grid, 1);

    u[0][0] = 1.0;
    u[1][0] = 1.0;

    IdentityOperator op;
    RK2 integrator;

    const double dt = 0.1;

    integrator.advance(u, op, dt);

    /* du/dt = u    
     k1 = 1.0
     u1 = 1.0 + 0.1 * 1.0 = 1.1
     k2 = 1.1
    
     u_new = 1.0 + 0.5 * 0.1 * (1.0 + 1.1)
           = 1.105
    */
    EXPECT_DOUBLE_EQ(u[0][0], 1.105);
    EXPECT_DOUBLE_EQ(u[1][0], 1.105);
}