cmake_minimum_required(VERSION 3.1...3.27)

project(ParticleSimulation CXX)

include_directories("SimulationConfig/simulationconfig.hpp"
                    "particle.hpp"
                    "simulation.hpp"
                    )

file (
    GLOB_RECURSE
    PartSim_SRCS
    "src/*.cpp"
    "src/*.hpp"
)

add_executable(run ${PartSim_SRCS})