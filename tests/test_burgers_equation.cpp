#include "physics/equations/BurgersEquation.h"
#include <gtest/gtest.h>

/* Number of conserved variables */
TEST(BurgersEquationTest, NumVariables){
    BurgersEquation equation;
    EXPECT_EQ(equation.numVariables(), 1u);
}

/* Flux */
TEST(BurgersEquationTest, FluxZero){
    BurgersEquation equation;
    Vector U{0.0};
    Vector F = equation.flux(U);
    EXPECT_DOUBLE_EQ(F[0], 0.0);
}

TEST(BurgersEquationTest, FluxPositive){
    BurgersEquation equation;
    Vector U{2.0};
    Vector F = equation.flux(U);
    EXPECT_DOUBLE_EQ(F[0], 2.0);
}

TEST(BurgersEquationTest, FluxNegative){
    BurgersEquation equation;
    Vector U{-2.0};
    Vector F = equation.flux(U);
    EXPECT_DOUBLE_EQ(F[0], 2.0);
}

TEST(BurgersEquationTest, FluxFraction){
    BurgersEquation equation;
    Vector U{0.5};
    Vector F = equation.flux(U);
    EXPECT_DOUBLE_EQ(F[0], 0.125);
}

/* Maximum wave speed */
TEST(BurgersEquationTest, WaveSpeedZero){
    BurgersEquation equation;
    Vector U{0.0};
    EXPECT_DOUBLE_EQ(equation.maxWaveSpeed(U), 0.0);
}

TEST(BurgersEquationTest, WaveSpeedPositive){
    BurgersEquation equation;
    Vector U{3.0};
    EXPECT_DOUBLE_EQ(equation.maxWaveSpeed(U), 3.0);
}

TEST(BurgersEquationTest, WaveSpeedNegative){
    BurgersEquation equation;
    Vector U{-3.0};
    EXPECT_DOUBLE_EQ(equation.maxWaveSpeed(U), 3.0);
}
