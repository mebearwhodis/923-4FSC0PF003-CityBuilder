#game

file(GLOB_RECURSE SRC_FILES src/*.cc)
file(GLOB_RECURSE HEADER_FILES include/*.h)

add_library(game ${SRC_FILES} ${HEADER_FILES})
target_include_directories(game PUBLIC include/)

target_link_libraries(game PRIVATE api sfml-system sfml-network sfml-graphics sfml-window sfml-audio)

if(ENABLE_PROFILING)
	target_link_libraries(game PUBLIC Tracy::TracyClient)
	target_compile_definitions(game PUBLIC TRACE_ENABLE=1)
endif(ENABLE_PROFILING)