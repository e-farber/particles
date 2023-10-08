#include "simulation.hpp"

#include <fstream>
#include <sstream>
#include <iomanip>
#include "auxiliary_math.hpp"

Simulation::Simulation(const SimulationConfig &simconfig)
    : configurations {simconfig} {
}


bool Simulation::to_VTK(std::string_view fileBaseName, const SimulationConfig &simconfig) {
/*
VTK file format documentation
https://docs.vtk.org/en/latest/design_documents/VTKFileFormats.html
*/

    // generate file name
    std::ostringstream fileName {};
    size_t digit_amount {std::to_string(configurations.total_iterations).length()};
    fileName << "../output/" << fileBaseName << "_"
             << std::setfill('0') << std::setw(digit_amount) << iteration_count
             << ".vtk";

    // open file
    std::ofstream vtkFile;
    vtkFile.open(fileName.str());
    if (!vtkFile.is_open()) {
        throw std::runtime_error
              ("Simulation::to_VTK(): Failed to open file \"" + fileName.str() + "\"");
    }

    // ### start writing ###
    // header
    vtkFile << "# vtk DataFile Version 3.0\n"
            << "Timestep " << iteration_count << "\n"
            << "ASCII\n";

    // particle positions
    std::vector<Particle> particles {simconfig.all_particles};
    vtkFile << "DATASET STRUCTURED_GRID\n"
            << "DIMENSIONS 1 1 1\n"
            << "POINTS " << particles.size() << " float\n";
    for (auto &particle : particles) {
        vtkFile << particle.position << "\n";
    }

    vtkFile << "\n";

    vtkFile << "POINT_DATA " << particles.size() << "\n";
    // particle velocities
    vtkFile << "VECTORS velocities float" << "\n";
    for (auto &particle : particles) {
      vtkFile << particle.velocity << "\n";
    }

    vtkFile << "\n";

    // particle forces
    vtkFile << "VECTORS forces float" << "\n";
    for (auto &particle : particles) {
      vtkFile << particle.force << "\n";
    }


    vtkFile << std::endl;
    return true;
}


void Simulation::execute_timestep(float timestep_dur, std::vector<Particle> &all_particles) {
    // calculate new force
    for (auto &particle : all_particles) {
        particle.force = {0.0, 0.0, 0.0};
        
        for (auto &other_particle : all_particles) {
            // case (particle == other_particle) is handled by calc_force
            particle.force += particle.calc_force(other_particle);
        }
    }

    // calculate new velocity
    for (auto &particle : all_particles) {
        particle.old_velocity = particle.velocity;
        vec3D new_velocity {particle.force * timestep_dur}; 
        particle.velocity += new_velocity;
    }

    // calculate new position
    for (auto &particle : all_particles) {
        vec3D distance_moved {particle.velocity * timestep_dur};
        particle.move_by(distance_moved);
    }

    ++iteration_count;
}