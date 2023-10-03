#pragma once

#include "SimulationConfig/simulationconfig.hpp"


// handles the simulation
class Simulation {
public:
    const SimulationConfig configurations;
    int iteration_count {0};

    Simulation() = default;

    // generates VTK file with particle data
    bool to_VTK(std::string_view fileBaseName, const SimulationConfig &simconfig);
    
    // simulate one timestep
    void execute_timestep(float timestep, std::vector<Particle> &all_particles);
};