#pragma once

#include "../particle.hpp"

/**
 * Stores simulation configurations.
 */
class SimulationConfig {
public:
    std::string sim_name {"no_name_defined"};
    int total_iterations {1};
    float timestep_dur {1.0};
    std::vector<Particle> all_particles;
    float cutoff_value {};

    SimulationConfig() = default;

    /**
     * Construct configurations by manually passing arguments.
     * @param sim_name Name of the simulation. Determines name of output files.
     * @param iterations Amount of total iterations.
     * @param timestep_dur Duration of one timestep in seconds.
     * @param particles Vector storing all particles to be simulated.
     */ 
    SimulationConfig(std::string_view sim_name,
                     const int iterations,
                     const float timestep_dur,
                     const std::vector<Particle> &particles,
                     const float cutoff_value);

    /**
     * Read configurations from YAML-file.
     * @param source_file_name Name of the YAML-file in "name.yaml" format from inside
     * "../input/"
     */
    void load(const std::string &source_file_name);
};