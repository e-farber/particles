#include <iostream>
#include <string>
#include "SimulationConfig/simulationconfig.hpp"
#include "particle.hpp"
#include "simulation.hpp"


int main() {
    // cube corner points
    std::vector<std::vector<float>> cube = 
                   {{0.0, 0.0, 0.0},   {5.0, 0.0, 0.0}, {10.0, 0.0, 0.0},
                    {0.0, 5.0, 0.0},   {5.0, 5.0, 0.0}, {10.0, 5.0, 0.0},
                    {0.0, 10.0, 0.0},  {5.0, 10.0, 0.0}, {10.0, 10.0, 0.0},
                    {0.0, 0.0, 5.0},   {5.0, 0.0, 5.0}, {10.0, 0.0, 5.0},
                    {0.0, 5.0, 5.0},   {5.0, 5.0, 5.0}, {10.0, 5.0, 5.0},
                    {0.0, 10.0, 5.0},  {5.0, 10.0, 5.0}, {10.0, 10.0, 5.0},
                    {0.0, 0.0, 10.0},  {5.0, 0.0, 10.0}, {10.0, 0.0, 10.0},
                    {0.0, 5.0, 10.0},  {5.0, 5.0, 10.0}, {10.0, 5.0, 10.0},
                    {0.0, 10.0, 10.0}, {5.0, 10.0, 10.0}, {10.0, 10.0, 10.0}};
;
;
    // create and fill vector of particles
    std::vector<Particle> all_particles {};
    for (auto &point : cube) {
        all_particles.emplace_back(point[0], point[1], point[2]);
    }
    std::vector<Particle> test_particles {};
    test_particles.emplace_back(-1.5, 0.0, 0.0);
    test_particles.emplace_back(1.0, 0.0, 0.0);
    Simulation sim;
    SimulationConfig cube_config(10'000, 0.002, test_particles);
    std::string loading_bar(40, '-');
    for (int iteration = 0; iteration < cube_config.total_iterations; ++iteration) {
        sim.to_VTK("cube", cube_config);
        
        if (iteration < 20) {
            std::cout << loading_bar << std::endl;
            loading_bar.replace(loading_bar.begin() + iteration / 250,
                                loading_bar.begin() + iteration / 250 + 2,
                                 "##");
            std::cout << test_particles[0].force[0] << "f\n"
                      << test_particles[0].old_velocity[0] << "ov\n"
                      << test_particles[0].velocity[0] << "v\n"
                      << test_particles[0].position.x_pos << "p\n\n";
        }
        // for (auto &particle : cube_config.all_particles) {
        //     std::cout << particle << "\n------------\n";
        // }
        sim.execute_timestep(cube_config.timestep, test_particles);
    }
    
    return 0;
}
