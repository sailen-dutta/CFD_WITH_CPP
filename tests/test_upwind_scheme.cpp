#include "core/Field1D.h"
#include "core/Grid1D.h"
#include "numerics/UpwindScheme.h"
#include <gtest/gtest.h>

TEST(UpwindSchemeTest, ConstantField){
    /* Constant field should remain constant */
    Grid1D grid(0.0, 1.0, 11);
    Field1D u(grid,1);

    u.fill(2.0);

    UpwindScheme scheme;

    scheme.step(u, 1.0, 0.01);

    for (std::size_t i = 0; i < u.size(); i++){
        EXPECT_DOUBLE_EQ(u[i][0], 2.0);
    }
}

TEST(UpwindSchemeTest, ZeroVelocityTest){
    /* If c = 0, then du/dt = 0 */
    Grid1D grid(0.0, 1.0, 11);
    Field1D u(grid,1);

    for (size_t i = 0; i < u.size(); ++i){
        u[i][0] = static_cast<double>(i);
    }
    Field1D u_initial = u;

    UpwindScheme scheme;

    scheme.step(u, 0.0, 0.01);

    for (size_t i = 0; i < u.size(); ++i){
        EXPECT_DOUBLE_EQ(u[i][0], u_initial[i][0]);
    }     
}

TEST(UpwindSchemeTest, PeriodicBC){
    /* To test correctness of periodic BC: After one time step, left boundary should receive the value at right boundary*/
    Grid1D grid(0.0, 1.0, 5);
    Field1D u(grid,1);

    u.fill(0.0);

    /* Non-zero value at right boundary */
    u[4][0] = 5.0;

    UpwindScheme scheme;

    double c = 1.0;
    double dt = 0.1;
    double dx = grid.dx();

    double cfl = (c * dt) / dx;

    scheme.step(u, c, dt);

    EXPECT_DOUBLE_EQ(u[0][0], 5 * cfl);
}

