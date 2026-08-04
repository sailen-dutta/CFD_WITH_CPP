#include "core/Field1D.h"
#include <gtest/gtest.h>

TEST(Field1DTest, ConstructorCreatesCorrectSize){
    Grid1D grid(0.0, 1.0, 11);
    Field1D u(grid,1);
    EXPECT_EQ(u.size(), 11);
}

TEST(Field1DTest, ValuesInitializedToZero){
    Grid1D grid(0.0, 1.0, 11);
    Field1D u(grid,1);
    for(size_t i = 0; i < u.size(); ++i){
        EXPECT_DOUBLE_EQ(u[i][0], 0.0);
    }
}

TEST(Field1DTest, AssignmentWorks){
    Grid1D grid(0.0, 1.0, 11);
    Field1D u(grid,1);
    u[5][0] = 3.14;
    EXPECT_DOUBLE_EQ(u[5][0], 3.14);
}

TEST(Field1DTest, FillWorks){
    Grid1D grid(0.0, 1.0, 11);
    Field1D u(grid,1);
    u.fill(3.5);
    for (size_t i = 0; i < u.size(); ++i){
        EXPECT_DOUBLE_EQ(u[i][0], 3.5);
    }
}

TEST(Field1DTest, GridAccess){
    Grid1D grid(0.0, 1.0, 11);
    Field1D u(grid,1);
    EXPECT_DOUBLE_EQ(u.grid().dx(), 0.1);
}

TEST(Field1DTest, AtThrowsOutOfRange){
    Grid1D grid(0.0, 1.0, 11);
    Field1D u(grid,1);
    EXPECT_THROW(u.at(11), std::out_of_range);
}
