#include "core/Grid1D.h"
#include <gtest/gtest.h>

TEST(Grid1DTest, ConstructorStoresBasicProperties){
    Grid1D grid1d(0.0, 1.0, 11);
    EXPECT_EQ(grid1d.size(), 11);
    EXPECT_DOUBLE_EQ(grid1d.x0(), 0.0);
    EXPECT_DOUBLE_EQ(grid1d.x1(), 1.0);
    EXPECT_DOUBLE_EQ(grid1d.dx(), 0.1);
}

TEST(Grid1DTest, CoordinatesAreGeneratedCorrectly){
    Grid1D grid1d(0.0, 1.0, 11);
    EXPECT_DOUBLE_EQ(grid1d.x(0), 0.0);
    EXPECT_DOUBLE_EQ(grid1d.x(1), 0.1);
    EXPECT_DOUBLE_EQ(grid1d.x(5), 0.5);
    EXPECT_DOUBLE_EQ(grid1d.x(10), 1.0);
}

TEST(Grid1DTest, CoordinatesVectorHasCorrectSize){
    Grid1D grid1d(-1.0,1.0,5);
    EXPECT_EQ(grid1d.coordinates().size(), 5);
}

TEST(Grid1DTest, ThrowsIfNxLessThanTwo){
    EXPECT_THROW(Grid1D(0.0, 1.0, 1),std::invalid_argument);
}

TEST(Grid1DTest, ThrowsIfX1LessThanOrEqualToX0){
    EXPECT_THROW(Grid1D(1.0, 0.0, 11),std::invalid_argument);

    EXPECT_THROW(Grid1D(0.0, 0.0, 11),std::invalid_argument);
}

TEST(Grid1DTest, XThrowsOnOutOfRangeAccess){
    Grid1D grid(0.0, 1.0, 11);

    EXPECT_THROW(grid.x(11),std::out_of_range);
}