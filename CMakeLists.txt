#root
cmake_minimum_required(VERSION 3.18)
project(CityBuilder)


set (CMAKE_CXX_STANDARD 20)
set (CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()
option(ENABLE_PROFILING "Enable Tracy Profiling" OFF)
    
find_package(GTest CONFIG REQUIRED)
find_package(SFML COMPONENTS system window graphics audio CONFIG REQUIRED)

if(ENABLE_PROFILING)
 	find_package(Tracy CONFIG REQUIRED)
endif(ENABLE_PROFILING)

add_subdirectory(core/)
add_subdirectory(api/)
add_subdirectory(game/)

add_executable(main main.cc)
target_link_libraries(main PRIVATE core api game sfml-system sfml-network sfml-graphics sfml-window sfml-audio)

if(ENABLE_PROFILING)
	target_link_libraries(main PUBLIC Tracy::TracyClient)
	target_compile_definitions(main PUBLIC TRACE_ENABLE=1)
endif(ENABLE_PROFILING)

# Copy resource files to the build directory
file(COPY ${CMAKE_SOURCE_DIR}/resources DESTINATION ${CMAKE_BINARY_DIR})