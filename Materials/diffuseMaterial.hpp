//
// Created by axell on 7/4/2021.
//

#ifndef RAYTRACER_DIFFUSEMATERIAL_HPP
#define RAYTRACER_DIFFUSEMATERIAL_HPP
#include "material.hpp"

class diffuseMaterial : public material {
public:
    diffuseMaterial(const color &a) : _color(a) {};


    bool scatter(const ray &r_in,
                 const contact &contact_data,
                 color &attenuation, ray &scattered) const override {
        vec3 scatter_direction = contact_data.normal + random_unit().unit_vector();
        if (near_zero(scatter_direction))
            scatter_direction = contact_data.normal;
        scattered = ray(contact_data.p, scatter_direction);
        attenuation = _color;
        return true;
    }

private:
    color _color;
};


#endif //RAYTRACER_DIFFUSEMATERIAL_HPP
