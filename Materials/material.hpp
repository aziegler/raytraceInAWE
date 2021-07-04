//
// Created by axell on 7/4/2021.
//

#ifndef RAYTRACER_MATERIAL_HPP
#define RAYTRACER_MATERIAL_HPP
#include "../ray.hpp"

struct contact;

class material {
public:
    virtual bool scatter(
            const ray& r_in, const contact& contact_data,color& attenuation, ray& scattered
            ) const = 0;

};



#endif //RAYTRACER_MATERIAL_HPP
