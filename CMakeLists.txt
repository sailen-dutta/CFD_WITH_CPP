cmake_minimum_required(VERSION 3.16)
project(CFD LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(vector STATIC 
            src/Vector.cpp)

target_include_directories(vector
    PUBLIC ${PROJECT_SOURCE_DIR}/include)

add_library(grid1d STATIC 
            src/Grid1D.cpp)    

target_include_directories(grid1d 
    PUBLIC ${PROJECT_SOURCE_DIR}/include)

target_link_libraries(grid1d PUBLIC vector)

add_library(field1d STATIC
            src/Field1D.cpp)

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

add_library(io STATIC src/CSVWriter.cpp)
target_include_directories(io PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(io PUBLIC field1d)

add_library(initial_conditions STATIC src/InitialConditions.cpp)
target_include_directories(initial_conditions PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(initial_conditions PUBLIC field1d)

add_executable(initialize_field apps/initialize_field.cpp)
target_link_libraries(initialize_field PRIVATE io initial_conditions field1d)

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