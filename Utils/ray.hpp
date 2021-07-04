//
// Created by axell on 7/4/2021.
//

#ifndef RAYTRACER_RAY_HPP
#define RAYTRACER_RAY_HPP


#include "vec3.hpp"

class ray {


public:
    ray() : _orig{0, 0, 0}, _dir{0, 0, 0} {};

    const vec3 &getOrig() const {
        return _orig;
    }

    const vec3 &getDir() const {
        return _dir;
    }

    point3 at(double t) const {
        return _orig + _dir * t;
    }

    ray(const point3& origin, const vec3& direction) : _orig(origin), _dir(direction) {}

private:
    vec3 _orig;
    vec3 _dir;
};


#endif //RAYTRACER_RAY_HPP
