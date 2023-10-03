#pragma once

#include "../particle.hpp"

class SimulationConfig {
public:
    const int total_iterations {1};
    const float timestep {0.05};
    std::vector<Particle> all_particles;

    SimulationConfig() = default;
    SimulationConfig(int iterations, float timestep, std::vector<Particle> particles);
};