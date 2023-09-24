#include "particle.hpp"
#include <cmath>
#include <iterator>

coordinates::coordinates(int x, int y, int z)
    : x_pos {x}, y_pos {y}, z_pos {z} {
    }



Particle::Particle()
    : position {0, 0, 0}, force {0}, velocity {0} {
    }

Particle::Particle(int x, int y, int z)
    : position {x, y, z}, force {0}, velocity {0} {
    }

bool Particle::move(const int new_x, const int new_y, const int new_z) {
    coordinates new_pos{new_x, new_y, new_z};
    position = new_pos; 
    return true;
}


double Particle::distance(const Particle &other) {
    int x_diff = position.x_pos - other.position.x_pos;
    int y_diff = position.y_pos - other.position.y_pos;
    int z_diff = position.z_pos - other.position.z_pos;

    return sqrt(x_diff * x_diff + y_diff * y_diff + z_diff *z_diff);
}


std::ostream& operator <<(std::ostream& os, const Particle particle) {
    os << "  # coords: " << "(" << particle.position.x_pos << ", " 
                            << particle.position.y_pos << ", "
                            << particle.position.z_pos << ")\n"
       << "  # other information to be implemented: " /* TODO */; 
    return os;
}


std::vector<Particle> Particle::find_neighbours(const std::vector<Particle> &all_particles,
                                                const                double dist) {
    std::vector<Particle> neighour_particles {};
    neighour_particles.reserve(all_particles.size());

    for (auto &other : all_particles) {
        double distance {this->distance(other)};
        
        if (distance <= dist && distance != 0) {
            neighour_particles.emplace_back(other);
        }
    }

    return neighour_particles;
}