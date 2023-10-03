
#include "simulationconfig.hpp"

SimulationConfig::SimulationConfig(int iterations, float timestep, std::vector<Particle> particles)
    : total_iterations {iterations}, timestep {timestep}, all_particles {particles} {
 }
