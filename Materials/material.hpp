//
// Created by axell on 7/4/2021.
//

#ifndef RAYTRACER_MATERIAL_HPP
#define RAYTRACER_MATERIAL_HPP
#include "../Utils/ray.hpp"

class material;

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

class material {
public:
    virtual bool scatter(
            const ray& r_in, const contact& contact_data,color& attenuation, ray& scattered
            ) const = 0;

};



#endif //RAYTRACER_MATERIAL_HPP
