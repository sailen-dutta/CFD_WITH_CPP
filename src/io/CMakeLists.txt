add_library(config STATIC
	config/ConfigReader.cpp
)

add_library(writers STATIC
	writers/CSVWriter.cpp
	writers/TecplotWriter1D.cpp
	writers/VTKWriter1D.cpp
	writers/OutputWriterFactory.cpp
)

add_library(output STATIC
	output/OutputManager.cpp
	output/RunSummaryWriter.cpp
)

target_include_directories(config
	PUBLIC
		${PROJECT_SOURCE_DIR}/include
)

target_include_directories(writers
	PUBLIC
		${PROJECT_SOURCE_DIR}/include
)

target_include_directories(output
	PUBLIC
		${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(config
	PUBLIC 
	 	core
		nlohmann_json::nlohmann_json
)

target_link_libraries(writers
	PUBLIC
		core
)

target_link_libraries(output
	PUBLIC
		core
		nlohmann_json::nlohmann_json
)




