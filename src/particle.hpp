#pragma once 

#include <iostream>
#include <vector>


struct coordinates {
    coordinates() = default;
    // initialize coordinates to x, y, z
    coordinates(int x, int y , int z );

    int x_pos {};
    int y_pos {};
    int z_pos {};
};


class Particle {
    public:

    coordinates position;
    
    // default constructor with position (0, 0, 0) 
    Particle();
    // construct particle with position = (x, y, z)
    Particle(int x, int y, int z);


    // move particle to new position
    bool move(const int new_x, const int new_y, const int new_z);

    // calculate distance between two particles
    double distance(const Particle &other);

    /*
    for this particle, check distance to all other particles in an array
    and return all particles with at most specified distance in a vector
    */

    friend std::ostream& operator <<(std::ostream& os, const Particle particle);
    static inline int total_amout_of_particles {100};

    template <size_t N>
    std::vector<Particle> find_neighbours(const Particle (&all_particles)[N], const double &distance = 5)
    {
    std::vector<Particle> neighbour_particles[N];
    for (auto & other_particle : all_particles) {
        if (distance(other_particle) <= distance && distance(other_particle) != 0) {
            neighbour_particles->push_back(other_particle);
        }
    }
    return neighbour_particles;
    }
};

constexpr int &N = Particle::total_amout_of_particles;