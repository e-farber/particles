#include "particle.hpp"
#include "auxiliary_math.hpp"
#include <cmath>
#include <iterator>
#include <iomanip> // std::setprecision

Particle::Particle(float x, float y, float z)
    : position {x, y, z} {
}

bool Particle::move(const float new_x, const float new_y, const float new_z) {
    vec3D new_pos {new_x, new_y, new_z};
    position = new_pos; 
    return true;
}


bool Particle::move(const vec3D &new_position) {
    position = new_position;
    return true;
}


bool Particle::move_by(const float x_offset, const float y_offset, const float z_offset) {
    vec3D offset {x_offset,
                  y_offset,
                  z_offset};
    
    position += offset;
    return true;
}

bool Particle::move_by(const vec3D &offset) {
    position += offset;
    return true;
}

vec3D Particle::vector_from(const Particle &other) {
    return position - other.position;
}

float Particle::distance(const Particle &other) {
    vec3D diff_vec {vector_from(other)};
    return diff_vec.length();
}


std::ostream& operator <<(std::ostream& os, const Particle &particle) {
    //os.precision(2);
    os /*<< std::setprecision(3)*/
       << "  # position:     " << particle.position     << "\n"
       << "  # force:        " << particle.force        << "\n"
       << "  # old_velocity: " << particle.old_velocity << "\n"
       << "  # velocity:     " << particle.velocity; 
    return os;
}


vec3D Particle::calc_force(const Particle &other) { // TODO double check if what i'm doing is correct
    float dist {distance(other)};
    
    if (dist == 0) {
        vec3D default_result {0.0, 0.0, 0.0};
        return default_result;
    }

    vec3D diff_vector {vector_from(other)};
    diff_vector /= dist;

    float force {auxmath::LJpot_derivative(dist)};
    diff_vector *= force;
    
    return diff_vector;
}


std::vector<Particle> Particle::find_neighbours(const std::vector<Particle> &all_particles,
                                                const float                 dist) {
    std::vector<Particle> neighour_particles {};
    neighour_particles.reserve(all_particles.size());

    for (auto &other : all_particles) {
        float distance {this->distance(other)};
        
        if (distance <= dist && distance != 0) {
            neighour_particles.emplace_back(other);
        }
    }

    return neighour_particles;
}