cmake_minimum_required(VERSION 3.16)
project(CFD LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
#     link_libraries(stdc++fs)
# endif()

# Compiler warning flags
if (MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -pedantic)
endif()

add_library(vector STATIC 
            src/core/Vector.cpp)

target_include_directories(vector
    PUBLIC ${PROJECT_SOURCE_DIR}/include)

add_library(grid1d STATIC 
            src/core/Grid1D.cpp)    

target_include_directories(grid1d 
    PUBLIC ${PROJECT_SOURCE_DIR}/include)

target_link_libraries(grid1d PUBLIC vector)

add_library(field1d STATIC
            src/core/Field1D.cpp)

target_include_directories(field1d
    PUBLIC ${PROJECT_SOURCE_DIR}/include)

target_link_libraries(field1d
    PUBLIC
        vector
        grid1d)

include(CTest)
enable_testing()

find_package(GTest REQUIRED)
include(GoogleTest)

find_package(nlohmann_json REQUIRED)

add_library(analysis STATIC
            src/analysis/ErrorAnalysis.cpp)
target_include_directories(analysis PUBLIC 
                           ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(analysis PUBLIC
                      field1d)      
add_library(io STATIC 
            src/io/CSVWriter.cpp
            src/io/VTKWriter1D.cpp
            src/io/TecplotWriter1D.cpp            
            src/io/OutputManager.cpp
            src/io/OutputWriterFactory.cpp
            src/io/ConfigReader.cpp)

target_include_directories(io PUBLIC 
                           ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(io PUBLIC 
                      field1d
                      nlohmann_json::nlohmann_json)

add_library(initial_conditions STATIC 
            src/physics/initial_conditions/InitialConditions.cpp
            src/physics/initial_conditions/InitialConditionFactory.cpp
            src/physics/ExactSolutions.cpp)
target_include_directories(initial_conditions PUBLIC 
                           ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(initial_conditions PUBLIC 
                      field1d)

add_executable(initialize_field 
               apps/initialize_field.cpp)
target_link_libraries(initialize_field PRIVATE 
                      io 
                      initial_conditions 
                      field1d)

add_library(advection STATIC 
            src/numerics/UpwindScheme.cpp 
            src/numerics/FTCS.cpp
            src/numerics/LaxFriedrichsScheme.cpp
            src/numerics/LaxWendroffScheme.cpp)

target_include_directories(advection PUBLIC 
                           ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(advection PUBLIC 
                      field1d)

add_executable(advection1d 
               apps/advection1d.cpp)

target_link_libraries(advection1d PRIVATE 
                      advection
                      io 
                      initial_conditions
                      analysis)
        
add_library(burgers STATIC            
            src/numerics/flux/RusanovFlux.cpp
            src/numerics/spatial/FirstOrderFVOperator.cpp
            src/numerics/time/ForwardEuler.cpp
            src/numerics/time/RK2.cpp)

target_include_directories(burgers PUBLIC 
                           ${PROJECT_SOURCE_DIR}/include)

target_link_libraries(burgers PUBLIC 
                      field1d)

add_executable(burgers1d
               apps/burgers1d.cpp)

target_link_libraries(burgers1d PRIVATE
                      burgers
                      io
                      initial_conditions
                      field1d
                      grid1d)          

###########################
###### Vector Tests #######
###########################
add_executable(test_vector
    tests/test_vector.cpp)

target_link_libraries(test_vector
    PRIVATE
        vector
        GTest::gtest_main)

gtest_discover_tests(test_vector)

###########################
###### Grid1D Tests #######
###########################
add_executable(test_grid1d
    tests/test_grid1d.cpp)

target_link_libraries(test_grid1d
    PRIVATE
        grid1d
        GTest::gtest_main
)

gtest_discover_tests(test_grid1d)

###########################
###### Field1D Tests #######
###########################
add_executable(test_field1d
    tests/test_field1d.cpp)

target_link_libraries(test_field1d
    PRIVATE
        field1d
        GTest::gtest_main)

gtest_discover_tests(test_field1d)


###########################
###### Error Analysis Tests
###########################
add_executable(test_error_analysis
               tests/test_error_analysis.cpp)

target_link_libraries(test_error_analysis
    PRIVATE
        analysis
        field1d
        grid1d
        GTest::gtest_main)

gtest_discover_tests(test_error_analysis)

###########################
###### Upwind Scheme Tests#
###########################
add_executable(test_upwind_scheme
               tests/test_upwind_scheme.cpp)

target_link_libraries(test_upwind_scheme
    PRIVATE
        advection
        field1d
        grid1d
        GTest::gtest_main)

gtest_discover_tests(test_upwind_scheme)