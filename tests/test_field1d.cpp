#include "Field1D.h"
#include <gtest/gtest.h>

TEST(Field1DTest, ConstructorCreatesCorrectSize){
    Grid1D grid(0.0, 1.0, 11);
    Field1D u(grid);
    EXPECT_EQ(u.size(), 11);
}

TEST(Field1DTest, ValuesInitializedToZero){
    Grid1D grid(0.0, 1.0, 11);
    Field1D u(grid);
    for(size_t i = 0; i < u.size(); ++i){
        EXPECT_DOUBLE_EQ(u[i], 0.0);
    }
}

TEST(Field1DTest, AssignmentWorks){
    Grid1D grid(0.0, 1.0, 11);
    Field1D u(grid);
    u[5] = 3.14;
    EXPECT_DOUBLE_EQ(u[5], 3.14);
}

TEST(Field1DTest, FillWorks){
    Grid1D grid(0.0, 1.0, 11);
    Field1D u(grid);
    u.fill(3.5);
    for (size_t i = 0; i < u.size(); ++i){
        EXPECT_DOUBLE_EQ(u[i], 3.5);
    }
}

TEST(Field1DTest, GridAccess){
    Grid1D grid(0.0, 1.0, 11);
    Field1D u(grid);
    EXPECT_DOUBLE_EQ(u.grid().dx(), 0.1);
}

TEST(Field1DTest, AtThrowsOutOfRange){
    Grid1D grid(0.0, 1.0, 11);
    Field1D u(grid);
    EXPECT_THROW(u.at(11), std::out_of_range);
}
