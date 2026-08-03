add_library(equations STATIC
	equations/BurgersEquation.cpp
)

add_library(exact_solutions STATIC
	exact_solutions/ExactSolutions.cpp
)

add_library(initial_conditions STATIC
	initial_conditions/InitialConditions.cpp
	initial_conditions/InitialConditionFactory.cpp
)

target_include_directories(equations
	PUBLIC
		${PROJECT_SOURCE_DIR}/include
)

target_include_directories(exact_solutions
	PUBLIC
		${PROJECT_SOURCE_DIR}/include
)

target_include_directories(initial_conditions
	PUBLIC
		${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(equations
	PUBLIC
		core
)

target_link_libraries(exact_solutions
	PUBLIC
		core
)

target_link_libraries(initial_conditions
	PUBLIC
		core
)


