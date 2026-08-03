add_executable(advection1d
    advection1d.cpp
)

target_link_libraries(advection1d
    PRIVATE
        core
        initial_conditions
        exact_solutions
        analysis
        advection
        writers
)

add_executable(burgers1d
    burgers1d.cpp
)

target_link_libraries(burgers1d
    PRIVATE 
    core
    initial_conditions
    flux
    spatial
    reconstruction
    time
    limiter
    config
    writers
    output
)

add_executable(initialize_field
    initialize_field.cpp
)

target_link_libraries(initialize_field
    PRIVATE
        core
        config
        initial_conditions
        writers
)