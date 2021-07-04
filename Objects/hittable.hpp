//
// Created by axell on 7/4/2021.
//

#ifndef RAYTRACER_HITTABLE_HPP
#define RAYTRACER_HITTABLE_HPP

#include "../Utils/vec3.hpp"
#include "../ray.hpp"
#include "../Materials/material.hpp"

struct contact {
    point3 p;
    vec3 normal;
    std::shared_ptr<material> mat_ptr;
    double t;
    bool front_face;

    inline void set_face_normal(const ray& r, const vec3& original_normal) {
        front_face = dot(r.getDir(), original_normal) < 0;
        normal = front_face ? original_normal : -original_normal;
    }
};



class hittable {
public:
    virtual bool hit(const ray& r, double t_min, double t_max, contact& rec) const = 0;
};

#endif //RAYTRACER_HITTABLE_HPP
