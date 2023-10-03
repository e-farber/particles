#include "particle.hpp"
#include "auxiliary_math.hpp"
#include <cmath>
#include <iterator>
#include <iomanip> // std::setprecision

coordinates::coordinates(float x, float y, float z)
    : x_pos {x}, y_pos {y}, z_pos {z} {
}



Particle::Particle()
    : position {0.0, 0.0, 0.0} {
}

Particle::Particle(float x, float y, float z)
    : position {x, y, z} {
}

bool Particle::move(const float new_x, const float new_y, const float new_z) {
    coordinates new_pos{new_x, new_y, new_z};
    position = new_pos; 
    return true;
}

bool Particle::move_by(const float x_offset, const float y_offset, const float z_offset) {
    coordinates new_pos {position.x_pos + x_offset,
                         position.y_pos + y_offset,
                         position.z_pos + z_offset};
    
    position = new_pos;
    return true;
}

bool Particle::move_by(const std::vector<float> &offset) {
    coordinates new_pos {position.x_pos + offset[0],
                         position.y_pos + offset[1],
                         position.z_pos + offset[2]};
    
    position = new_pos;
    return true;
}

std::vector<float> Particle::vector_from(const Particle &other) {
    std::vector<float> result;
    result.reserve(3);

    result.emplace_back(position.x_pos - other.position.x_pos);
    result.emplace_back(position.y_pos - other.position.y_pos);
    result.emplace_back(position.z_pos - other.position.z_pos);

    return result;
}


float Particle::distance(const Particle &other) {
    float x_diff = position.x_pos - other.position.x_pos;
    float y_diff = position.y_pos - other.position.y_pos;
    float z_diff = position.z_pos - other.position.z_pos;

    return sqrt(x_diff * x_diff + y_diff * y_diff + z_diff *z_diff);
}


std::ostream& operator <<(std::ostream& os, const Particle particle) {
    os.precision(2);
    os << std::setprecision(3)
       << "  # coords:       (" << particle.position.x_pos << ", " 
                                 << particle.position.y_pos << ", "
                                 << particle.position.z_pos << ")\n"
       << "  # force:        (" << particle.force[0] << ", "
                                 << particle.force[1] << ", "
                                 << particle.force[2] << ")\n"
       << "  # old_velocity: (" << particle.old_velocity[0] << ","
                                << particle.old_velocity[1] << ","
                                << particle.old_velocity[2] << ")\n"
       << "  # velocity:     (" << particle.velocity[0] << ","
                                << particle.velocity[1] << ","
                                << particle.velocity[2] << ")"; 
    return os;
}


std::vector<float> Particle::calc_force(const Particle &other) {
    float dist {distance(other)};
    
    if (dist == 0) {
        std::vector<float> default_result {0, 0, 0};
        return default_result;
    }

    std::vector<float> diff_vector {vector_from(other)};
    float force {LJpot_der(dist)};
    ScalarMultiplication(force, diff_vector);
    
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