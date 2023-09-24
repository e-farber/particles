#include "simulation.hpp"
#include <fstream>
#include <sstream>
#include <iomanip>

bool Simulation::to_VTK(std::string_view fileBaseName) {
/*
VTK file format documentation
https://docs.vtk.org/en/latest/design_documents/VTKFileFormats.html
*/

    // generate file name
    std::ostringstream fileName {};
    int digit_amount {std::to_string(configurations.total_iterations).length()};
    fileName << fileBaseName << "_" << std::setfill('0') << std::setw(digit_amount)
                << iteration_count << ".vtk";

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
    std::vector<Particle> particles; // TODO initialize properly 
    vtkFile << "DATASET STRUCTURED_GRID\n"
            << "DIMENSIONS 1 1 1\n"
            << "POINTS " << particles.size() << " double\n";
    for (auto &point : particles) {
        vtkFile << point.position.x_pos << " " << point.position.y_pos << " "
                << point.position.z_pos << "\n";
    }

    vtkFile << "POINT_DATA " << particles.size() << "\n";
    // TODO

    vtkFile << std::endl;
    vtkFile.close();
    return true;
}