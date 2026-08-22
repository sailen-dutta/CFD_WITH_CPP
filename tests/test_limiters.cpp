#include "numerics/limiter/UnlimitedLimiter.h"
#include "numerics/limiter/MinmodLimiter.h"
#include <gtest/gtest.h>

TEST(UnlimitedLimiterTest, AveragesLeftAndRightSlopes){
    UnlimitedLimiter limiter;

    /* Unlimited limiter uses:
       slope = 0.5 * (left + right)
       For left = 2 and right = 4
       slope = 0.5 * (2 + 4) = 3
    */
   EXPECT_DOUBLE_EQ(limiter.limit(2.0,4.0),3.0);
}

TEST(UnlimitedLimiterTest, EqualSlopes){
    UnlimitedLimiter limiter;

    /* If both one-sided slopes are equal, 
       the unlimited slope value should be exactly that value
    */
   EXPECT_DOUBLE_EQ(limiter.limit(3.0,3.0), 3.0);
}

TEST(UnlimitedLimiterTest, OppositeSlopes){
    UnlimitedLimiter limiter;

    /* Opposite slopes cancel */
    EXPECT_DOUBLE_EQ(limiter.limit(2.0, -2.0), 0.0);
}

TEST(UnlimitedLimiterTest, NegativeSlopes){
    UnlimitedLimiter limiter;

    /* The same averaging rule must work for negative slopes as well */
    EXPECT_DOUBLE_EQ(limiter.limit(-2.0, -4.0), -3.0);
}

TEST(MinModLimiterTest, PositiveSlope){
    MinmodLimiter limiter;

    /* If both slopes are positive, left = 2 and right = 4
       minmod(2,4) = 2
    */
   EXPECT_DOUBLE_EQ(limiter.limit(2.0, 4.0), 2);
}

TEST(MinModLimiterTest, NegativeSlope){
    MinmodLimiter limiter;

    /* If both slopes are negative, left = -2 and right = -4
       minmod(-2,-4) = -2
    */
   EXPECT_DOUBLE_EQ(limiter.limit(-2.0, -4.0), -2.0);
}

TEST(MinModLimiterTest, OppositeSignReturnsZero){
    MinmodLimiter limiter;

    /* If both slopes have opposite signs, left = -2 and right = 4
       Then, this indicates local extremum.
       So, minmod returns 0 to avoid creating a new slope 
    */
   EXPECT_DOUBLE_EQ(limiter.limit(-2.0, 4.0), 0.0);
}

TEST(MinModLimiterTest, ZeroSlopeReturnsZero){
    MinmodLimiter limiter;

    /* If either slope is zero, then minmod returns 0 */
    EXPECT_DOUBLE_EQ(limiter.limit(0.0, 4.0), 0.0);
    EXPECT_DOUBLE_EQ(limiter.limit(4.0, 0.0), 0.0);
}


