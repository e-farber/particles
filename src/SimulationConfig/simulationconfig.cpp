
#include "simulationconfig.hpp"
#include <yaml-cpp/yaml.h>

SimulationConfig::SimulationConfig(std::string_view sim_name,
                                   const int iterations,
                                   const float timestep_dur,
                                   const std::vector<Particle> &particles,
                                   const float cutoff_value)
    : sim_name         {sim_name},
      total_iterations {iterations},
      timestep_dur     {timestep_dur},
      all_particles    {particles},
      cutoff_value     {cutoff_value} {
}


void SimulationConfig::load(const std::string &fileName) {
    std::string directory_name {"../input/"};
    const std::string path {std::move(directory_name.append(fileName))};
    const YAML::Node config {YAML::LoadFile(path)};

    sim_name           = config["Simulation_Name"  ].as<std::string>();
    total_iterations   = config["Iterations"       ].as<int>();
    timestep_dur       = config["Timestep_Duration"].as<float>();
    cutoff_value       = config["Cutoff_Value"     ].as<float>();

    const YAML::Node &positions_node {config["Particle_Positions"]};
    for (auto position_iterator {positions_node.begin()};
         position_iterator    != positions_node.end();
         ++position_iterator) {
        auto position {*position_iterator};
        all_particles.emplace_back(position[0].as<float>(),
                                   position[1].as<float>(),
                                   position[2].as<float>());
    }
}