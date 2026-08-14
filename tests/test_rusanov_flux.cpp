#include "numerics/flux/RusanovFlux.h"
#include "physics/equations/BurgersEquation.h"

#include <gtest/gtest.h>

TEST(RusanovFluxTest, ConstantZeroState){
    BurgersEquation equation;
    RusanovFlux flux;

    Vector left{0.0};
    Vector right{0.0};

    Vector result = flux.compute(left, right, equation);

    EXPECT_DOUBLE_EQ(result[0], 0.0);
}

TEST(RusanovFluxTest, ConstantStateEqualsPhysicalFlux){
    BurgersEquation equation;
    RusanovFlux flux;

    Vector left{2.0};
    Vector right{2.0};

    Vector result = flux.compute(left, right, equation);

    /* For identical states Rusanov flux must equal the physical flux */
    Vector expected = equation.flux(left);

    EXPECT_DOUBLE_EQ(result[0], expected[0]);
}

TEST(RusanovFluxTest, KnownBurgersFlux){
    BurgersEquation equation;
    RusanovFlux flux;

    Vector left{2.0};
    Vector right{1.0};

    Vector result = flux.compute(left, right, equation);

    /* Burgers flux: F(u) = 1/2 u^2
       Therefore: FL = 1/2 * 2^2 = 2
                  FR = 1/2 * 1^2 = 0.5
        
       Max wave speed: a = max(|2|, |1|) = 2
       Rusanov Flux: F = 1/2(FL + FR) - 1/2 a (UR - UL)
                       = 1/2 * (2 + 0.5) - 1/2 * 2 * (1 - 2)
                       = 2.25
    */
    EXPECT_DOUBLE_EQ(result[0], 2.25);
}

TEST(RusanovFluxTest, ReversedStates){
    BurgersEquation equation;
    RusanovFlux flux;

    Vector left{1.0};
    Vector right{2.0};

    Vector result = flux.compute(left, right, equation);

    EXPECT_DOUBLE_EQ(result[0], 0.25);
}

TEST(RusanovFluxTest, SymmetricZeroStates){
    BurgersEquation equation;
    RusanovFlux flux;
    Vector left{-1.0};
    Vector right{1.0};
    Vector result = flux.compute(left, right, equation);
    EXPECT_DOUBLE_EQ(result[0], -0.5);
}