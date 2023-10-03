#pragma once

#include <cmath>
#include <vector>

/*
Calculates the Lennard-Jones-Potential.

@param r        distance between two particles
@param epsilon  depth of potential well
@param sigma    size of the particle

@return         Lennard-Jones-Potential
*/
inline float LJpot(const float r, const float epsilon = 0.997, const float sigma = 3.4) {
    float fraction {sigma / r};
    float diff {   std::pow(fraction, static_cast<float>(12.0))
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
inline float LJpot_der(const float r, const float epsilon = 0.997, const float sigma = 3.4) {
    float fraction {sigma / r};    
    float diff {2 * std::pow(fraction, static_cast<float>(12.0))
                  - std::pow(fraction, static_cast<float>( 6.0))};
 
    return 24 * epsilon * (1 / r) * diff;
}


// out-of-place entry-wise addition of two vectors
template <typename T>
std::vector<T> VectorAddition_oop(const std::vector<T> &v1, const std::vector<T> &v2) {
    int v1_size = v1.size();

    if (v1_size != v2.size()) {
        throw std::invalid_argument("vectors differ in size");
    }


    std::vector<T> result;
    result.reserve(v1_size);

    for (int index = 0; index < v1_size; ++index) {
       result.emplace_back(v1[index] + v2[index]); 
    }

    return result;
}

// in-place entry-wise addition of two vectors (first argument is modified)
template <typename T>
void VectorAddition_ip(std::vector<T> &v1, const std::vector<T> &v2) {
    int v1_size = v1.size();

    if (v1_size != v2.size()) {
        throw std::invalid_argument("vectors differ in size");
    }

    for (int index = 0; index < v1_size; ++index) {
       v1[index] += v2[index];
    }
}

// in-place scalar multiplication of input vector
template <typename T>
std::vector<T> ScalarMultiplication(const T scalar, std::vector<T> &input_vector) {
    for (auto &it : input_vector) {
        it *= scalar;
    }

    return input_vector;
}