#include "numerics/flux/RusanovFlux.h"
#include "numerics/flux/FluxFactory.h"
#include <stdexcept>
#include <gtest/gtest.h>

TEST(FluxFactoryTest, CreatesRusanov){
    /* The flux factory should create a RusanovFlux when given the string "rusanov" */
    auto flux = FluxFactory::create("rusanov");

    ASSERT_NE(flux, nullptr);

    /* The factory returns a unique_ptr<NumericalFlux>.
       Check that the actual object is of type RusanovFlux */

    EXPECT_NE(dynamic_cast<RusanovFlux*>(flux.get()), nullptr);
}

TEST(FluxFactoryTest, UnknownFluxThrows){
    EXPECT_THROW(FluxFactory::create("unknown"), std::runtime_error);
}

TEST(FluxFactoryTest, EmptyFluxNameThrows){
    EXPECT_THROW(FluxFactory::create(""), std::runtime_error);
}