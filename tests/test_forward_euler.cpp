#include "numerics/time/ForwardEuler.h"
#include "numerics/spatial/SpatialOperator.h"
#include "core/Grid1D.h"
#include "core/Field1D.h"
#include "core/Vector.h"
#include <gtest/gtest.h>

class ConstantRHSOperator : public SpatialOperator {
    public:
        explicit ConstantRHSOperator(const Vector &rhs) : rhs_(rhs) {}
        void computeRHS(const Field1D& u, Field1D& rhs) const override {
            ASSERT_EQ(rhs.numVariables(), rhs_.size());
            for (std::size_t i = 0; i < u.size(); ++i){
                rhs[i] = rhs_;
            }
        }
    private:
        Vector rhs_;
};

TEST(ForwardEulerTest, UpdatesStatusUsingRHS){
    Grid1D grid(0.0, 1.0, 3);
    Field1D u(grid, 1);

    for (std::size_t i = 0; i < u.size(); ++i){
        u[i][0] = 1.0;
    }

    Vector rhs_value(1);
    rhs_value[0] = 2.0;

    ConstantRHSOperator op(rhs_value);
    ForwardEuler integrator;

    const double dt = 0.1;

    integrator.advance(u, op, dt);

    /* Forward Euler:
       U^(n+1) = U^n + dt * RHS
               = 1.0 + 0.1 * 2.0
               = 1.2
    */
    for (std::size_t i = 0; i < u.size(); ++i){
        EXPECT_DOUBLE_EQ(u[i][0], 1.2);
    }
}

TEST(ForwardEulerTest, ZeroRHSLeavesStateUnchanged){
    Grid1D grid(0.0, 1.0, 3);
    Field1D u(grid, 1);

    for (std::size_t i = 0; i < u.size(); ++i){
        u[i][0] = static_cast<double>(i+1);
    }

    Field1D original = u;
    Vector rhs_value(1);
    rhs_value[0] = 0.0;

    ConstantRHSOperator op(rhs_value);
    ForwardEuler integrator;

    integrator.advance(u, op, 0.1);

    for (std::size_t i = 0; i < u.size(); ++i){
        EXPECT_DOUBLE_EQ(u[i][0], original[i][0]);
    }
}

TEST(ForwardEulerTest, UpdatesAllValues){
    Grid1D grid(0.0, 1.0, 2);
    Field1D u(grid, 3);

    for (std::size_t i = 0; i < u.size(); ++i){
        u[i][0] = 1.0;
        u[i][1] = 2.0;
        u[i][2] = 3.0;
    }

    Vector rhs_value(3);
    rhs_value[0] = 10.0;
    rhs_value[1] = -2.0;
    rhs_value[2] = 0.5;

    ConstantRHSOperator op(rhs_value);
    ForwardEuler integrator;

    const double dt = 0.1;

    integrator.advance(u, op, dt);

    /* Every conserved variable must be updated 
       U0 = 1 + 0.1*10 = 2.0
       U1 = 2 + 0.1*(-2) = 1.8
       U2 = 3 + 0.1*0.5 = 3.05 */
    for (std::size_t i = 0; i < u.size(); ++i){
        EXPECT_DOUBLE_EQ(u[i][0], 2.0);
        EXPECT_DOUBLE_EQ(u[i][1], 1.8);
        EXPECT_DOUBLE_EQ(u[i][2], 3.05);
    }
}