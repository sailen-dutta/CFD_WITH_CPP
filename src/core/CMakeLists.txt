add_library(core STATIC
	Vector.cpp
	Grid1D.cpp
	Field1D.cpp
)

target_include_directories(core 
	PUBLIC
		${PROJECT_SOURCE_DIR}/include
)

