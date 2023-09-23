#include <iostream>
#include <string>
#include "particle.hpp"


int main() {
    Particle all_particles[N];
    for (int index = 0; index < N; ++index) {
        Particle p {index, index*2, -index*3};
        all_particles[index] = p;
    }

    std::cout << "distance: " << all_particles[0].distance(all_particles[99]) << std::endl;

    std::cout << "distance: " << all_particles[13].distance(all_particles[18]) << std::endl;

    std::cout << all_particles[38] << std::endl;
    
    std::cout << all_particles[50].find_neighbours(all_particles).size();
    
    return 0;
}
