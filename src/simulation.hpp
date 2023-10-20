#pragma once

#include "SimulationConfig/simulationconfig.hpp"
#include <string_view>


// handles the simulation
class Simulation {
private:
    int iteration_count {0};

public:
    SimulationConfig configurations;

    Simulation() = default;
    Simulation(const SimulationConfig &simconfig);

    // generates VTK file with particle data
    bool to_VTK(const SimulationConfig &simconfig);
    
    // simulate one timestep
    void execute_timestep(float timestep_dur, std::vector<Particle> &all_particles);

    /**
     * does particle simulation and generates vtk files
     * 
     * Simulation object has to have instantiated configurations member variable
     * that's where information on simulation is taken from
     */
    void simulate();
};