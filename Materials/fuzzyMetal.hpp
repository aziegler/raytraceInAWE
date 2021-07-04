//
// Created by axell on 7/4/2021.
//

#ifndef RAYTRACER_FUZZYMETAL_HPP
#define RAYTRACER_FUZZYMETAL_HPP
#include "metalMaterial.hpp"

class fuzzyMetal : public metalMaterial{

public:
    fuzzyMetal(const color &a, double fuzzyness) : metalMaterial(a), _fuzyness(fuzzyness < 2 ? fuzzyness : 2) {}

    vec3 metalReflect(const vec3 inbound, const vec3 normal) const override {
        vec3 init =  metalMaterial::metalReflect(inbound, normal);
        vec3 random = random_vector() * _fuzyness;
        return init + random;
    }

private:
    double _fuzyness;
};


#endif //RAYTRACER_FUZZYMETAL_HPP
