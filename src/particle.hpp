#pragma once 

#include "vec3D.hpp"
#include <iostream>
#include <vector>
#include <cmath>


/**
  * 
  * 
  * 
  */
class Particle {
public:
    vec3D position     {};
    vec3D force        {};
    vec3D old_velocity {};
    vec3D velocity     {};
    

    // default constructor with all member values set to (0, 0, 0)
    Particle() = default;
    // construct particle with position = (x, y, z), everything else set to (0, 0, 0)
    Particle(float x, float y, float z);



    // overloaded operators
    friend std::ostream& operator << (std::ostream& os, const Particle &particle);
   


    // move particle to new absolute position
    bool move(const float new_x, const float new_y, const float new_z);
    bool move(const vec3D &new_position);

    // move particle to new relative position
    bool move_by(const float x_offset, const float y_offset, const float z_offset);
    bool move_by(const vec3D &offset);

    // return distance vector between this and other particle
    vec3D vector_from(const Particle &other);

    // calculates and returns distance to other particle
    float distance(const Particle &other);

    // calculate force vector acting on particle by other particle
    vec3D calc_force(const Particle &other);

    /*
    for this particle, check distance to all other particles in a vector
    and return a vector with all particles with at most specified distance (excluding this)
    */
    std::vector<Particle> find_neighbours(const std::vector<Particle> &all_particles, const float dist);
};