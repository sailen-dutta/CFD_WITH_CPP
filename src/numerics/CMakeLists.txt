add_library(advection STATIC
	FTCS.cpp
	LaxFriedrichsScheme.cpp
	LaxWendroffScheme.cpp
	UpwindScheme.cpp
)

target_include_directories(advection
	PUBLIC
		${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(advection
	PUBLIC
		core
)

add_library(limiter STATIC
	limiter/MinmodLimiter.cpp
	limiter/SuperbeeLimiter.cpp
	limiter/UnlimitedLimiter.cpp
	limiter/VanLeerLimiter.cpp
	limiter/SlopeLimiterFactory.cpp
)

target_include_directories(limiter
	PUBLIC
		${PROJECT_SOURCE_DIR}/include
)

add_library(reconstruction STATIC
	reconstruction/MUSCLReconstruction.cpp
	reconstruction/PiecewiseConstantReconstruction.cpp
	reconstruction/ReconstructionFactory.cpp
)

target_include_directories(reconstruction
	PUBLIC
		${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(reconstruction
	PUBLIC
		core
		limiter
)

add_library(flux STATIC
	flux/FluxFactory.cpp
	flux/RusanovFlux.cpp
)

target_include_directories(flux
	PUBLIC
		${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(flux
	PUBLIC
		core
		equations
)

add_library(spatial STATIC
	spatial/FiniteVolumeSpatialOperator.cpp
)

target_include_directories(spatial
	PUBLIC
		${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(spatial
	PUBLIC
		core
		equations
)

add_library(time STATIC
	time/ForwardEuler.cpp
	time/RK2.cpp
	time/SSPRK3.cpp
	time/TimeIntegratorFactory.cpp
)

target_include_directories(time
	PUBLIC
		${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(time
	PUBLIC
		core
)

