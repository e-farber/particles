#pragma once

#include <cmath>

// custom functions for calculations
namespace auxmath {
/*
Calculates the Lennard-Jones-Potential.

@param r        distance between two particles
@param epsilon  depth of potential well
@param sigma    size of the particle

@return         Lennard-Jones-Potential
*/
inline float LJpot(const float r,
                   const float epsilon = 0.997,
                   const float sigma = 3.4) {
    float fraction {sigma / r};
    float diff {   std::pow(fraction, static_cast<float>(12.0)) // TODO get rid of pow
                 - std::pow(fraction, static_cast<float>( 6.0)) };
    
    return diff * 4 * epsilon;
}


/*
Derivative of the Lennard-Jones-Potential.

@param r        distance between two particles
@param epsilon  depth of potential well
@param sigma    size of the particle

@return        Force
*/
inline float LJpot_derivative(const float r,
                              const float epsilon = 0.997,
                              const float sigma = 3.4) {
    float fraction {sigma / r};    
    float diff {2 * std::pow(fraction, static_cast<float>(12.0))
                  - std::pow(fraction, static_cast<float>( 6.0))};
 
    return 24 * epsilon * (1 / r) * diff;
}

} // end namespace auxmath