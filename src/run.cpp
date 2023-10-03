#include <iostream>
#include <string>
#include "SimulationConfig/simulationconfig.hpp"
#include "particle.hpp"
#include "simulation.hpp"


int main() {
    // cube corner points
    std::vector<std::vector<float>> cube = {{0.0,  0.0, 0.0}, {2.5,  0.0, 0.0}, {0.0,  0.0, 2.5},
                                            {2.5,  0.0, 2.5}, {0.0, -2.5, 0.0}, {2.5, -2.5, 0.0},
                                            {0.0, -2.5, 2.5}, {2.5, -2.5, 2.5}};
    // create and fill vector of particles
    std::vector<Particle> all_particles {};
    for (auto &point : cube) {
        all_particles.emplace_back(point[0], point[1], point[2]);
    }

    Simulation sim;
    SimulationConfig cube_config(100, 0.05, all_particles);
    for (int iteration = 0; iteration < cube_config.total_iterations; ++iteration) {
        sim.to_VTK("cube", cube_config);
        std::cout << "\n\n########## iteration " << iteration << " ##########\n";
        for (auto &particle : cube_config.all_particles) {
            std::cout << particle << "\n------------\n";
        }
        sim.execute_timestep(cube_config.timestep, cube_config.all_particles);
    }
    
    return 0;
}
