cmake_minimum_required(VERSION 3.1...3.27)

project(ParticleSimulation CXX)

include(FetchContent)

FetchContent_Declare(
        yaml-cpp
        GIT_REPOSITORY "https://github.com/jbeder/yaml-cpp.git"
        GIT_TAG "yaml-cpp-0.6.3"
)

FetchContent_MakeAvailable(yaml-cpp)

file (
    GLOB_RECURSE
    PartSim_SRCS
    "src/*.cpp"
    "src/*.hpp"
)

add_executable(run ${PartSim_SRCS})


# general flags
set(CMAKE_CXX_FLAGS
	"${CMAKE_CXX_FLAGS}\
	-Wall\
	-Wextra\
	-Wpedantic\
	-fdiagnostics-color=always"
)

# debug flags
set(CMAKE_CXX_FLAGS_DEBUG
	"${CMAKE_CXX_FLAGS_DEBUG}\
	-g3\
	-Wdouble-promotion\
	-fsanitize=undefined\
	-fsanitize=address"
)

set(CMAKE_EXE_LINKER_FLAGS_DEBUG # sanitizer flags must be added both to compiler and linker
	"${CMAKE_EXE_LINKER_FLAGS_DEBUG}\
	-fsanitize=undefined\
	-fsanitize=address"
)
                                                    
target_link_libraries(run yaml-cpp)