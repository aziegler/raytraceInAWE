//
// Created by axell on 7/4/2021.
//

#ifndef RAYTRACER_HITTABLE_HPP
#define RAYTRACER_HITTABLE_HPP

#include "../Utils/vec3.hpp"
#include "../Utils/ray.hpp"
#include "../Materials/material.hpp"





class hittable {
public:
    virtual bool hit(const ray& r, double t_min, double t_max, contact& rec) const = 0;
};

#endif //RAYTRACER_HITTABLE_HPP
