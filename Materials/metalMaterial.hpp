//
// Created by axell on 7/4/2021.
//

#ifndef RAYTRACER_METALMATERIAL_HPP
#define RAYTRACER_METALMATERIAL_HPP
#include "material.hpp"

class metalMaterial : public material{
public:
    metalMaterial(const color &a) : _color(a) {};


    virtual vec3 metalReflect(const vec3 inbound, const vec3 normal) const{
        return reflect(inbound, normal);
    }

    bool scatter(const ray &r_in,
                 const contact &contact_data,
                 color &attenuation, ray &scattered) const override {
        vec3 scatter_direction = reflect(r_in.getDir(),contact_data.normal);
        scattered = ray(contact_data.p, scatter_direction);
        attenuation = _color;
        return (dot(scattered.getDir(), contact_data.normal) > 0);
    }

private:
    color _color;
};


#endif //RAYTRACER_METALMATERIAL_HPP
