#pragma once

#include <cmath>

// custom functions for calculations
namespace auxmath {

/**
 * calculates the lennard-Jones-Potential.
 * 
 * @param r        distance between two particles
 * @param epsilon  depth of potential well
 * @param sigma    size of the particle

 * @return         lennard-Jones-Potential
 */
inline float ljpot(const float r,
                   const float epsilon = 1.0,
                   const float sigma = 1.0) {
    float fraction {sigma / r};
    float fraction_to_pow_6 {fraction * fraction * fraction * fraction * fraction * fraction};
    float diff {fraction_to_pow_6 * fraction_to_pow_6 - fraction_to_pow_6};
    
    return diff * 4 * epsilon;
}


/**
 * Derivative of the Lennard-Jones-Potential.

 * @param r        distance between two particles
 * @param epsilon  depth of potential well
 * @param sigma    size of the particle

 * @return        Force
 */
inline float LJpot_derivative(const float r,
                              const float epsilon = 1.0,
                              const float sigma = 1.0) {
    float fraction {sigma / r};    
    float fraction_to_pow_6 {fraction * fraction * fraction * fraction * fraction * fraction};
    float diff {2 * fraction_to_pow_6 * fraction_to_pow_6 - fraction_to_pow_6};
 
    return 24 * epsilon * (1 / r) * diff;
}

} // end namespace auxmath