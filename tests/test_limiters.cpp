#include "numerics/limiter/UnlimitedLimiter.h"
#include "numerics/limiter/MinmodLimiter.h"
#include "numerics/limiter/VanLeerLimiter.h"
#include "numerics/limiter/SuperbeeLimiter.h"
#include "numerics/limiter/SlopeLimiterFactory.h"
#include <gtest/gtest.h>
#include <memory>

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

TEST(VanLeerLimiterTest, PositiveSlopes){
   VanLeerLimiter limiter;
   /* Both slopes are positive:
      left = 2, right = 4
      VanLeer limiter = 2*2*4 / (2+4)
                      = 16/6 = 8/3
   */
  EXPECT_DOUBLE_EQ(limiter.limit(2.0, 4.0), 8.0/3.0);
}

TEST(VanLeerLimiterTest, NegativeSlopes){
   VanLeerLimiter limiter;
   EXPECT_DOUBLE_EQ(limiter.limit(-2.0, -4.0), -8.0/3.0);
}

TEST(VanLeerLimiterTest, OppositeSignReturnsZero){
   VanLeerLimiter limiter;
   /* Implementation returns 0, if left * right <= 0 */
   EXPECT_DOUBLE_EQ(limiter.limit(-2.0, 4.0), 0.0);
   EXPECT_DOUBLE_EQ(limiter.limit(5.0, -4.0), 0.0);
}

TEST(VanLeerLimiterTest, ZeroSlopeReturnsZero){
   VanLeerLimiter limiter;
   EXPECT_DOUBLE_EQ(limiter.limit(0.0, 4.0), 0.0);
   EXPECT_DOUBLE_EQ(limiter.limit(2.0, 0.0), 0.0);
}

TEST(SuperbeeLimiterTest, PositiveSlopes){
   SuperbeeLimiter limiter;

   /* Both slopes are positive:
      left = 2, right = 4
      Candidate 1:
                  a = min(2*2, 4)\
                    = min (4,4)
                    = 4
      
      Candidate 2:
                  b = min(2, 2*4)
                    = min(2, 8)
                    = 2
      Superbee chooses max of (a,b) = 4
   */
  EXPECT_DOUBLE_EQ(limiter.limit(2.0, 4.0), 4.0);
}

TEST(SuperbeeLimiterTest, NegativeSlopes){
   SuperbeeLimiter limiter;

   /* Both slopes are negative:
      left = -2, right = -4
      The limiter works with magnitude first
      a = min(2*2, 4) = 4
      b = min(2, 2*4) = 2
      The larger magnitude is 4
      Since the original slopes were negative, the result must also be negative
   */
   EXPECT_DOUBLE_EQ(limiter.limit(-2.0, -4.0), -4.0);
}

TEST(SuperbeeLimiterTest, OppositeSignReturnsZero){
   SuperbeeLimiter limiter;
   EXPECT_DOUBLE_EQ(limiter.limit(-2.0, 4.0), 0.0);
   EXPECT_DOUBLE_EQ(limiter.limit(2.0, -4.0), 0.0);
}

TEST(SuperbeeLimiterTest, ZeroSlopeReturnsZero){
   SuperbeeLimiter limiter;
   EXPECT_DOUBLE_EQ(limiter.limit(0.0, 4.0), 0.0);
   EXPECT_DOUBLE_EQ(limiter.limit(4.0, 0.0), 0.0);
}

TEST(SuperbeeLimiterTest, ChoosesLargerCandidate)
{
    SuperbeeLimiter limiter;

    /* This test specifically exercises the max(a,b) part of the Superbee formula.
       left  = 4
       right = 2

       Candidate 1:
                   a = min(2*4, 2)
                     = min(8, 2)
                     = 2
       Candidate 2:
                   b = min(4, 2*2)
                     = min(4, 4)
                     = 4
       Therefore: max(a,b) = 4
    */
    EXPECT_DOUBLE_EQ(limiter.limit(4.0, 2.0), 4.0);
}

TEST(SlopeLimiterFactoryTest, CreatesUnlimitedLimiter){
   /* The string "unlimited" should create and UnlimitedLimiter object */
   auto limiter = SlopeLimiterFactory::create("unlimited");
   ASSERT_NE(limiter, nullptr);
   EXPECT_NE(dynamic_cast<UnlimitedLimiter*>(limiter.get()), nullptr);
}

TEST(SlopeLimiterFactoryTest, CreatesMinmodLimiter){
   auto limiter = SlopeLimiterFactory::create("minmod");
   ASSERT_NE(limiter, nullptr);
   EXPECT_NE(dynamic_cast<MinmodLimiter*>(limiter.get()), nullptr);
}

TEST(SlopeLimiterFactoryTest, CreatesVanLeerLimiter){
   auto limiter = SlopeLimiterFactory::create("vanleer");
   ASSERT_NE(limiter, nullptr);
   EXPECT_NE(dynamic_cast<VanLeerLimiter*>(limiter.get()), nullptr);
}

TEST(SlopeLimiterFactoryTest, CreatesSuperbeeLimiter){
   auto limiter = SlopeLimiterFactory::create("superbee");
   ASSERT_NE(limiter, nullptr);
   EXPECT_NE(dynamic_cast<SuperbeeLimiter*>(limiter.get()), nullptr);
}

TEST(SlopeLimiterFactoryTest, UnknownLimiterThrows){
   EXPECT_THROW(SlopeLimiterFactory::create("unknown"), std::runtime_error);
}

