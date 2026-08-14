add_executable(test_error_analysis
    test_error_analysis.cpp
)

target_link_libraries(test_error_analysis
    PRIVATE
        core
        analysis
        GTest::gtest_main
)

gtest_discover_tests(test_error_analysis)

add_executable(test_field1d
    test_field1d.cpp
)

target_link_libraries(test_field1d
    PRIVATE
        core
        GTest::gtest_main
)

gtest_discover_tests(test_field1d)

add_executable(test_grid1d
    test_grid1d.cpp
)

target_link_libraries(test_grid1d
    PRIVATE
        core
        GTest::gtest_main
)

gtest_discover_tests(test_grid1d)

add_executable(test_upwind_scheme
    test_upwind_scheme.cpp
)

target_link_libraries(test_upwind_scheme
    PRIVATE
        core
        advection
        GTest::gtest_main
)

gtest_discover_tests(test_upwind_scheme)

add_executable(test_vector
    test_vector.cpp
)

target_link_libraries(test_vector
    PRIVATE
        core
        GTest::gtest_main
)

gtest_discover_tests(test_vector)

add_executable(test_burgers_equation
    test_burgers_equation.cpp)

target_link_libraries(test_burgers_equation
    PRIVATE
        equations
        GTest::gtest_main
)

gtest_discover_tests(test_burgers_equation)

add_executable(test_rusanov_flux
    test_rusanov_flux.cpp)

target_link_libraries(test_rusanov_flux
    PRIVATE
        flux
        GTest::gtest_main
)

gtest_discover_tests(test_rusanov_flux)