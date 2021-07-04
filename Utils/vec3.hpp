//
// Created by axell on 7/4/2021.
//

#ifndef RAYTRACER_VEC3_HPP
#define RAYTRACER_VEC3_HPP

#include <cmath>

class vec3 {


public:
    vec3() : e{0, 0, 0} {}

    vec3(double v1, double v2, double v3) : e{v1, v2, v3} {}

    double x() const { return e[0]; }

    double y() const { return e[1]; }

    double z() const { return e[2]; }

    vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); }

    double operator[](int i) const { return e[i]; }

    vec3 &operator+=(const vec3 &v) {
        e[0] += v[0];
        e[1] += v[1];
        e[2] += v[2];
        return *this;
    }

    vec3 &operator*=(const double t) {
        e[0] *= t;
        e[1] *= t;
        e[2] *= t;
        return *this;
    }

    vec3 operator*(const double t) const {
        return vec3(e[0] * t, e[1] * t, e[2] * t);
    }

    double length_squared() const {
        return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
    }

    double length() const {
        return sqrt(length_squared());
    }

    vec3 unit_vector() const {
        return *this * (1.0 / length());
    }


private:
    double e[3];
};


using point3 = vec3;   // 3D point
using color = vec3;    // RGB color

inline vec3 operator+(const vec3 &first, const vec3 &other) {
    return vec3(first[0] + other[0], first[1] + other[1], first[2] + other[2]);
}

inline vec3 operator-(const vec3 &first, const vec3 &other) {
    return vec3(first[0] - other[0], first[1] - other[1], first[2] - other[2]);
}

inline double dot(const vec3 &first, const vec3 &other) {
    return first[0] * other[0] + first[1] * other[1] + first[2] * other[2];
}

inline vec3 operator*(const vec3 &first, const vec3 &other) {
    return vec3(first[0] * other[0], first[1] * other[1], first[2] * other[2]);
}

vec3 refract(const vec3& uv, const vec3& n, double etai_over_etat) {
    auto cos_theta = fmin(dot(-uv, n), 1.0);
    vec3 r_out_perp =  (uv + n * cos_theta) * etai_over_etat;
    vec3 r_out_parallel = n * -sqrt(fabs(1.0 - r_out_perp.length_squared())) ;
    return r_out_perp + r_out_parallel;
}

vec3 reflect(const vec3 inbound, const vec3 normal) {
    return inbound - normal * (2 * dot(normal,inbound));
}

inline vec3 cross(const vec3 &u, const vec3 &v) {
    return vec3(u[1] * v[2] - u[2] * v[1],
                u[2] * v[0] - u[0] * v[2],
                u[0] * v[1] - u[1] * v[0]);
}

#endif //RAYTRACER_VEC3_HPP
