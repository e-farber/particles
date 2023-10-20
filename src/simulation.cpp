#include "simulation.hpp"

#include <fstream>
#include <sstream>
#include <iomanip>
#include <filesystem>
#include "auxiliary_math.hpp"

Simulation::Simulation(const SimulationConfig &simconfig)
    : configurations {simconfig} {
}


bool Simulation::to_VTK(const SimulationConfig &simconfig) {
/*
VTK file format documentation/
https://docs.vtk.org/en/latest/design_documents/VTKFileFormats.html
*/
    // create output directory if not exists
    if (not std::filesystem::exists("../output/")) {
        std::filesystem::create_directory("../output/");
    }

    // generate file name
    std::ostringstream fileName {};
    size_t digit_amount {};
    const int powers_of_ten[6] {10, 100, 1'000, 10'000, 100'000, 1'000'000};
    for (int index {0}; index < 6; ++index) {
        if (configurations.total_iterations == powers_of_ten[index]) {
            digit_amount = std::to_string(configurations.total_iterations).length() - 1;
            break;
        }
        else {
            digit_amount = std::to_string(configurations.total_iterations).length();
        }
    }
   
    fileName << "../output/" << configurations.sim_name << "_"
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

void Simulation::simulate() {
    const std::string line(43, '-');
    std::cout << line << "\n"
              << "Simulation start.\n"
              << "Simulating " << configurations.all_particles.size() << " particles\n"
              << "over " << configurations.total_iterations << " iterations\n"
              << "with " << configurations.timestep_dur << " seconds between each iteration\n"
              << "for a total duration of "
              << configurations.total_iterations * configurations.timestep_dur << " seconds.\n"
              << line << "\n" << std::endl;

    std::cout << "->" << std::string(40, '#') << "|";

    using seconds = std::chrono::seconds;
    auto start_time {std::chrono::system_clock::now()};

    for (int iteration = 0; iteration < configurations.total_iterations; ++iteration) {
        if (iteration % (configurations.total_iterations / 20) == 0) {
            const int x_out_of_ten {1 + (iteration * 20) / configurations.total_iterations};
            std::cout << std::flush << "\r" << std::string(x_out_of_ten * 2, '-') << "->";
        }
        
        to_VTK(configurations);
        
        execute_timestep(configurations.timestep_dur,
                         configurations.all_particles);
    }

    auto end_time {std::chrono::system_clock::now()};
    std::chrono::duration total_time {std::chrono::duration_cast<seconds>(end_time - start_time)};
    std::cout << "\n\n"
              << line << "\n"
              << "Simulation end.\n"
              << "Time taken: " << total_time.count()  << " seconds.\n"
              << line << std::endl;
}