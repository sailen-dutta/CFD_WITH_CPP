add_library(analysis STATIC
	ErrorAnalysis.cpp
)

target_include_directories(analysis
	PUBLIC
		${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(analysis PUBLIC
		      core
)
