#include <iostream>
#include <string>
#include "SimulationConfig/simulationconfig.hpp"
#include "particle.hpp"
#include "simulation.hpp"
#include <chrono>


int main() {

    SimulationConfig configurations;
    configurations.load("octagon.yaml");
    Simulation test_sim(configurations);

    test_sim.simulate();
   
    return 0;
}
