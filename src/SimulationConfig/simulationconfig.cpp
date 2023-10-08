
#include "simulationconfig.hpp"

SimulationConfig::SimulationConfig(int iterations,
                                   float timestep_dur,
                                   std::vector<Particle> particles)
    : total_iterations {iterations}, timestep_dur {timestep_dur}, all_particles {particles} {
 }
