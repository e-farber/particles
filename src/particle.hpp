#pragma once 

#include <iostream>
#include <vector>
#include <cmath>


struct coordinates {
    coordinates() = default;
    // initialize coordinates to x, y, z
    coordinates(float x, float y , float z );

    float x_pos {};
    float y_pos {};
    float z_pos {};
};


class Particle {
public:
    coordinates position;
    std::vector<float> force        {0.0, 0.0, 0.0};
    std::vector<float> old_velocity {0.0, 0.0, 0.0};
    std::vector<float> velocity     {0.0, 0.0, 0.0};
    

    // default constructor with position = (0, 0, 0) 
    Particle();

    // construct particle with position = (x, y, z)
    Particle(float x, float y, float z);



    // overloaded operators
    friend std::ostream& operator <<(std::ostream& os, const Particle particle);
   


    // move particle to new absolute position
    bool move(const float new_x, const float new_y, const float new_z);

    // move particle to new relative position
    bool move_by(const float x_offset, const float y_offset, const float z_offset);
    bool move_by(const std::vector<float> &offset);

    // return distance vector between this and other particle
    std::vector<float> vector_from(const Particle &other);

    // calculate distance to other particle
    float distance(const Particle &other);

    // calculate force vector acting on particle by other particle
    std::vector<float> calc_force(const Particle &other);

    /*
    for this particle, check distance to all other particles in a vector
    and return a vector with all particles with at most specified distance (excluding this)
    */
    std::vector<Particle> find_neighbours(const std::vector<Particle> &all_particles, const float dist);
};