#include "numerics/time/TimeIntegratorFactory.h"
#include "numerics/time/ForwardEuler.h"
#include "numerics/time/RK2.h"
#include "numerics/time/SSPRK3.h"
#include <memory>
#include <stdexcept>
#include <gtest/gtest.h>

TEST(TimeIntegratorFactoryTest, CreatesForwardEuler){
    auto integrator = TimeIntegratorFactory::create("forward_euler");
    ASSERT_NE(integrator, nullptr);
    EXPECT_NE(dynamic_cast<ForwardEuler*>(integrator.get()), nullptr);
}

TEST(TimeIntegratorFactoryTest, CreatesRK2){
    auto integrator = TimeIntegratorFactory::create("rk2");
    ASSERT_NE(integrator, nullptr);
    EXPECT_NE(dynamic_cast<RK2*>(integrator.get()), nullptr);
}

TEST(TimeIntegratorFactoryTest, CreatesSSPRK3){
    auto integrator = TimeIntegratorFactory::create("ssprk3");
    ASSERT_NE(integrator, nullptr);
    EXPECT_NE(dynamic_cast<SSPRK3*>(integrator.get()), nullptr);
}

TEST(TimeIntegratorFactoryTest, UnknownIntegratorThrows){
    EXPECT_THROW(TimeIntegratorFactory::create("unknown"), std::runtime_error);
}


