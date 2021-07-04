//
// Created by axell on 7/4/2021.
//

#ifndef RAYTRACER_DIELECTRICMATERIAL_HPP
#define RAYTRACER_DIELECTRICMATERIAL_HPP

#include "material.hpp"

class dielectricMaterial : public material {

public:
    dielectricMaterial(color color, double ref) : _color(color), _refraction(ref) {}

    bool scatter(const ray &r_in, const contact &contact_data, color &attenuation, ray &scattered) const override {
        double refraction = contact_data.front_face ? (1.0 / _refraction) : _refraction;
        vec3 dir = r_in.getDir().unit_vector();
        auto cos_theta = fmin(dot(-dir, contact_data.normal), 1.0);
        auto sin_theta = sqrt(1.0 - cos_theta * cos_theta);
        if (refraction * sin_theta > 1.0|| reflectance(cos_theta,refraction) > random_double()) {
            vec3 reflection = reflect(dir, contact_data.normal);
            scattered = ray(contact_data.p, reflection);
        } else {
            vec3 refracted = refract(dir, contact_data.normal, refraction);
            scattered = ray(contact_data.p, refracted);
        }
        attenuation = _color;
        return true;
    }

private:
    color _color;
    double _refraction;

    static double reflectance(double cos, double re) {
        auto r0 = (1 - re) / (1 + re);
        r0 = r0 * r0;
        return r0 + (1 - r0) * pow((1 - cos), 5);
    }
};


#endif //RAYTRACER_DIELECTRICMATERIAL_HPP
