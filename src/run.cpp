#include <iostream>
#include <string>
#include "particle.hpp"

int particle_amount {100};

void create_particles(std::vector<Particle> &all_particles, int amount) {
    for (int index = 0; index < amount; ++index) {
        all_particles.emplace_back(index, -index, index);
    }    
}


int main() {
    std::vector<Particle> all_particles;
    all_particles.reserve(particle_amount);
    create_particles(all_particles, 100);

    std::cout << "distance: " << all_particles[0].distance(all_particles[99]) << std::endl;

    std::cout << "distance: " << all_particles[13].distance(all_particles[18]) << std::endl;

    std::cout << all_particles[38] << std::endl;
    
    std::cout << all_particles[50].find_neighbours(all_particles, 9.5).size() << std::endl;
    for (auto &it : all_particles[30].find_neighbours(all_particles, 9.5)) {
        std::cout << "distance = " << all_particles[30].distance(it) << "\n";
        std::cout << it << "\n";
    }
    
    return 0;
}
