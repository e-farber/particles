#pragma once 

#include <iostream>
#include <vector>
#include <cmath>


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
    // ### member values ###

    coordinates position;
    double force {0};
    double velocity {0};
    

    // default constructor with position = (0, 0, 0) 
    Particle();

    // construct particle with position = (x, y, z)
    Particle(int x, int y, int z);


    // overloaded operators
    friend std::ostream& operator <<(std::ostream& os, const Particle particle);
   

    // ### member functions ###

    // move particle to new position
    bool move(const int new_x, const int new_y, const int new_z);

    // calculate distance to other particle
    double distance(const Particle &other);

    /*
    for this particle, check distance to all other particles in a vector
    and return a vector with all particles with at most specified distance (excluding this)
    */
    std::vector<Particle> find_neighbours(const std::vector<Particle> &all_particles, const double dist);
};