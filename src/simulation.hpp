#pragma once

#include "particle.hpp"
#include "SimulationConfig/simulationconfig.hpp"

/*
Calculates the Lennard-Jones-Potential.

@param r        distance between two particles
@param epsilon  depth of potential well
@param sigma    size of the particle
*/
double LJpot(const double r, const double epsilon = 0.9, const double sigma = 0.1) {
    double fraction = sigma/r;
    double diff = std::pow(fraction, 12.0)- std::pow(fraction, 6.0);
    
    return diff * 4 * epsilon;
}


class Simulation {
    public:
    const SimulationConfig configurations;
    int iteration_count {0};


    bool to_VTK(std::string_view fileBaseName);


};