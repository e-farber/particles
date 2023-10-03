#include "simulation.hpp"

#include <fstream>
#include <sstream>
#include <iomanip>
#include "auxiliary_math.hpp"


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
        vtkFile << particle.position.x_pos << " " << particle.position.y_pos << " "
                << particle.position.z_pos << "\n";
    }

    // vtkFile << "POINT_DATA " << particles.size() << "\n";
    // TODO

    vtkFile << std::endl;
    return true;
}


void Simulation::execute_timestep(float timestep, std::vector<Particle> &all_particles) {
    // calculate new force
    for (auto &particle : all_particles) {
        particle.force = {0.0,
                          0.0,
                          0.0};
        for (auto &other_particle : all_particles) {
            // case (particle == other_particle) is handled by calc_force
            VectorAddition_ip(particle.force, particle.calc_force(other_particle));
        }
    }

    // calculate new velocity
    for (auto &particle : all_particles) {
        particle.old_velocity = particle.velocity;
        std::vector<float> new_velocity {ScalarMultiplication(timestep, particle.force)};
        VectorAddition_ip(particle.velocity, new_velocity); 
    }

    // calculate new position
    for (auto &particle : all_particles) {
        std::vector<float> distance_moved {ScalarMultiplication(timestep, particle.velocity)};
        particle.move_by(distance_moved);
    }

    ++iteration_count;
}