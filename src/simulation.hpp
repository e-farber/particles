#pragma once

#include "SimulationConfig/simulationconfig.hpp"


// handles the simulation
class Simulation {
private:
    int iteration_count {0};
public:
    const SimulationConfig configurations;

    Simulation() = default;
    Simulation(const SimulationConfig &simconfig);

    // generates VTK file with particle data
    bool to_VTK(std::string_view fileBaseName, const SimulationConfig &simconfig);
    
    // simulate one timestep
    void execute_timestep(float timestep_dur, std::vector<Particle> &all_particles);
};