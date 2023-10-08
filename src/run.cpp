#include <iostream>
#include <string>
#include "SimulationConfig/simulationconfig.hpp"
#include "particle.hpp"
#include "simulation.hpp"


int main() {
    // cube corner points
    std::vector<std::vector<float>> cube = 
                   {{0.0, 0.0, 0.0},   {5.0, 0.0, 0.0},   {10.0, 0.0, 0.0},
                    {0.0, 5.0, 0.0},   {5.0, 5.0, 0.0},   {10.0, 5.0, 0.0},
                    {0.0, 10.0, 0.0},  {5.0, 10.0, 0.0},  {10.0, 10.0, 0.0},
                    {0.0, 0.0, 5.0},   {5.0, 0.0, 5.0},   {10.0, 0.0, 5.0},
                    {0.0, 5.0, 5.0},   {5.0, 5.0, 5.0},   {10.0, 5.0, 5.0},
                    {0.0, 10.0, 5.0},  {5.0, 10.0, 5.0},  {10.0, 10.0, 5.0},
                    {0.0, 0.0, 10.0},  {5.0, 0.0, 10.0},  {10.0, 0.0, 10.0},
                    {0.0, 5.0, 10.0},  {5.0, 5.0, 10.0},  {10.0, 5.0, 10.0},
                    {0.0, 10.0, 10.0}, {5.0, 10.0, 10.0}, {10.0, 10.0, 10.0}};
;
;
    // create and fill vector of particles
    std::vector<Particle> all_particles {};
    for (auto &point : cube) {
        all_particles.emplace_back(point[0], point[1], point[2]);
    }

    Simulation sim;
    SimulationConfig cube_config(15'000, 0.002, all_particles);
    std::string loading_bar(40, '-');
    for (int iteration = 0; iteration < cube_config.total_iterations; ++iteration) {
        sim.to_VTK("cube", cube_config);
        
        if (iteration % 500 == 0) {
            std::cout << loading_bar;
            loading_bar.replace(loading_bar.begin() + iteration / 250,
                                loading_bar.begin() + iteration / 250 + 2,
                                 "##");
        }

        sim.execute_timestep(cube_config.timestep_dur, cube_config.all_particles);
    }
    
    return 0;
}
