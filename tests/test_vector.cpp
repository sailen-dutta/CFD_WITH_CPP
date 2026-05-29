#include "Vector.h"
#include<gtest/gtest.h>

TEST(VectorTest, DefaultConstructor){
    Vector v;
    EXPECT_TRUE(v.empty());
    EXPECT_EQ(v.size(),0);
}

TEST(VectorTest, SizedConstructorInitializesToZero){
    Vector v(5);
    EXPECT_EQ(v.size(), 5);
    for (size_t i = 0; i < v.size(); i++){
        EXPECT_EQ(v[i],0);
    }
}

TEST(VectorTest, FillConstructor){
    Vector v(4,2.5);
    for (double x: v){
        EXPECT_DOUBLE_EQ(x,2.5);
    }
}

TEST(VectorTest, InitializerListConstructor){
    Vector v{1.0, 2.0, 3.0};
    EXPECT_EQ(v.size(),3);
    EXPECT_DOUBLE_EQ(v[0], 1.0);
    EXPECT_DOUBLE_EQ(v[2],3.0);
}

TEST(VectorTest, Fill){
    Vector v(5);
    v.fill(7.0);
    for (double x : v){
        EXPECT_DOUBLE_EQ(x,7.0);
    }
}

TEST(VectorTest, Sum){
    Vector v{1.0, 2.0, 3.0};
    EXPECT_DOUBLE_EQ(v.sum(),6.0);
}

TEST(VectorTest, NormL2){
    Vector v{3.0, 4.0};
    EXPECT_DOUBLE_EQ(v.normL2(), 5.0);
}

TEST(VectorTest, NormInf){
    Vector v{-1.0, 7.0, -5.0};
    EXPECT_DOUBLE_EQ(v.normInf(), 7.0);
}

TEST(VectorTest, NormInfThrowsOnEmptyVector) {
    Vector v;
    EXPECT_THROW(v.normInf(), std::runtime_error);
}

TEST(VectorTest, MinThrowsOnEmptyVector) {
    Vector v;

    EXPECT_THROW(v.min(), std::runtime_error);
}

TEST(VectorTest, MaxThrowsOnEmptyVector) {
    Vector v;

    EXPECT_THROW(v.max(), std::runtime_error);
}

TEST(VectorTest, SumOfEmptyVectorIsZero) {
    Vector v;

    EXPECT_DOUBLE_EQ(v.sum(), 0.0);
}

TEST(VectorTest, MinMax){
    Vector v{3.0, -2.0, 9.0};
    EXPECT_DOUBLE_EQ(v.min(), -2.0);
    EXPECT_DOUBLE_EQ(v.max(), 9.0);
}

TEST(VectorTest, AtThrowsOutOfRange){
    Vector v(3);
    EXPECT_THROW(v.at(10), std::out_of_range);
}

TEST(VectorTest, SizedConstructorCreatesCorrectSize){
    Vector v(11);

    EXPECT_EQ(v.size(), 11);

    for (std::size_t i = 0; i < v.size(); ++i) {
        v[i] = static_cast<double>(i);
    }

    EXPECT_DOUBLE_EQ(v[10], 10.0);
}