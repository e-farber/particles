#include "vec3D.hpp"
#include <cmath>


vec3D::vec3D(float x, float y, float z)
    : x {x}, y {y} , z {z} {    
}


float vec3D::length() {
    float sum_of_squares {x*x + y*y + z*z};
    return std::sqrt(sum_of_squares);
}

vec3D& vec3D::operator+= (const vec3D &other) {
    x += other.x;
    y += other.y;
    z += other.z;
    
    return *this;
}


vec3D& vec3D::operator-= (const vec3D &other) {
    x -= other.x;
    y -= other.y;
    z -= other.z;

    return *this;
}


vec3D& vec3D::operator*= (const float scalar) {
    x *= scalar;
    y *= scalar;
    z *= scalar;

    return *this;
}


vec3D& vec3D::operator/= (const float scalar) {
    x /= scalar;
    y /= scalar;
    z /= scalar;

    return *this;
}

vec3D operator+ (vec3D lhs, const vec3D &rhs) {
   lhs += rhs;
   return lhs; 
}


vec3D operator- (vec3D lhs, const vec3D &rhs) {
    lhs -= rhs;
    return lhs;
}


vec3D vec3D::operator* (const float scalar) {
    vec3D result {x * scalar,
                  y * scalar,
                  z * scalar};

    return result;
}


vec3D operator* (const float scalar, vec3D vec) {
    vec *= scalar;
    return vec;    
}


vec3D vec3D::operator/ (const float scalar) {
    vec3D result {x / scalar,
                  y / scalar,
                  z / scalar};

    return result;
}


vec3D operator/ (const float scalar, vec3D vec) {
    vec /= scalar;
    return vec;
}

std::ostream& operator<<(std::ostream& os, const vec3D vec) {
    os << "(" << vec.x << ", "
              << vec.y << ", "
              << vec.z << ")";
    return os;
}
