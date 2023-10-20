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

target_link_libraries(run yaml-cpp)