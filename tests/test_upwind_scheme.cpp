#include "core/Field1D.h"
#include "core/Grid1D.h"
#include "numerics/UpwindScheme.h"
#include <gtest/gtest.h>

TEST(UpwindSchemeTest, ConstantField){
    /* Constant field should remain constant */
    Grid1D grid(0.0, 1.0, 11);
    Field1D u(grid);

    u.fill(2.0);

    UpwindScheme scheme;

    scheme.step(u, 1, 0.01);

    for (size_t i = 0; i < u.size(); i++){
        EXPECT_DOUBLE_EQ(u[i], 2.0);
    }
}

TEST(UpwindSchemeTest, ZeroVelocityTest){
    /* If c = 0, then du/dt = 0 */
    Grid1D grid(0.0, 1.0, 11);
    Field1D u(grid);

    for (size_t i = 0; i < u.size(); ++i){
        u[i] = static_cast<double>(i);
    }
    Field1D u_initial = u;

    UpwindScheme scheme;

    scheme.step(u, 0.0, 0.01);

    for (size_t i = 0; i < u.size(); ++i){
        EXPECT_DOUBLE_EQ(u[i], u_initial[i]);
    }     
}

TEST(UpwindSchemeTest, PeriodicBC){
    /* To test correctness of periodic BC: After one time step, left boundary should receive the value at right boundary*/
    Grid1D grid(0.0, 1.0, 5);
    Field1D u(grid);

    u.fill(0.0);

    /* Non-zero value at right boundary */
    u[4] = 5.0;

    UpwindScheme scheme;

    double c = 1.0;
    double dt = 0.1;
    double dx = grid.dx();

    double cfl = (c * dt) / dx;

    scheme.step(u, c, dt);

    EXPECT_DOUBLE_EQ(u[0], 5 * cfl);
}

