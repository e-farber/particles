#pragma once

#include <iostream>

/**
 * class for 3D coordinates
 * behaves like mathematical 3-dim vector
 * supports addition and scalar multiplication
 */
class vec3D {
private:
    float x {0.0};
    float y {0.0};
    float z {0.0};

public:
    // default constructor with entries (0, 0, 0)
    vec3D() = default;
    // constructs vec3D with entries (x, y, z)
    vec3D(float x, float y, float z);

    // calculates and returns euclidian length of vector
    float length();

    // compound assignment
    vec3D& operator+= (const vec3D &other);
    vec3D& operator-= (const vec3D &other);
    vec3D& operator*= (const float scalar);
    vec3D& operator/= (const float scalar);

    // binary operators
    friend vec3D operator+ (vec3D lhs, const vec3D &rhs);
    friend vec3D operator- (vec3D lhs, const vec3D &rhs);
           vec3D operator* (const float scalar);
    friend vec3D operator* (const float scalar, vec3D vec);
           vec3D operator/ (const float scalar);
    friend vec3D operator/ (const float scalar, vec3D vec);

    friend std::ostream& operator<<(std::ostream& os, const vec3D particle);
};