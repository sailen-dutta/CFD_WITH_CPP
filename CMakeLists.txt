cmake_minimum_required(VERSION 3.16)

PROJECT(CFD LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(MSVC)
	add_compile_options(/W4)
else()
	add_compile_options(-Wall -Wextra -pedantic)
endif()

find_package(GTest REQUIRED)
find_package(nlohmann_json REQUIRED)

include(CTest)
enable_testing()

add_subdirectory(src/core)
add_subdirectory(src/analysis)
add_subdirectory(src/io)
add_subdirectory(src/physics)
add_subdirectory(src/numerics)

add_subdirectory(apps)
add_subdirectory(tests)


