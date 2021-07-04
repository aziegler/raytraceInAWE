//
// Created by axell on 7/4/2021.
//

#ifndef RAYTRACER_WORLD_HPP
#define RAYTRACER_WORLD_HPP


#include "hittable.hpp"
#include "../Materials/diffuseMaterial.hpp"
#include "../Materials/fuzzyMetal.hpp"
#include "../Materials/dielectricMaterial.hpp"

#include <memory>
#include <vector>

class world : public hittable {
public:
    world() = default;

    world(std::shared_ptr<hittable> object) { add(object); }

    void clear() {
        _objects.clear();
    };

    void add(std::shared_ptr<hittable> object) {
        _objects.push_back(object);
    }

    bool hit(const ray &r, double t_min, double t_max, contact &rec) const override {
        contact temp_rec;
        bool hit_something = false;
        auto current_t = t_max;

        for(const auto &object : _objects) {
            if (object -> hit(r,t_min,current_t,temp_rec)){
                hit_something = true;
                current_t = temp_rec.t;
                rec = temp_rec;
            }
        }
        return hit_something;
    }



private:
    std::vector <std::shared_ptr<hittable>> _objects;
};

world random_scene() {
    world world;
    double scene_width = 8;
    double scene_depth = 8;

    auto ground_material = make_shared<diffuseMaterial>(color(0.5, 0.6, 0.5));
    world.add(make_shared<sphere>(point3(0, -1000, 0), 1000, ground_material));

    for (int a = 0; a < 60; ++a) {

        double radius = random_double(0.1, 0.7);
        point3 center(random_double(-1.0, 1.0) * scene_width, radius, random_double(-1.0, 1.0) * scene_depth);
        color color = random_color();

        shared_ptr<material> sphere_material;
        double mat_roll = random_double(0.0, 1.0);
        if (mat_roll < 0.5) {
            world.add(make_shared<sphere>(center, radius, make_shared<diffuseMaterial>(color)));
        } else if (mat_roll < 0.9) {
            world.add(make_shared<sphere>(center, radius, make_shared<fuzzyMetal>(color, radius)));
        } else {
            world.add(make_shared<sphere>(center, radius, make_shared<dielectricMaterial>(color, 1.5)));
        }
    }
    return world;
}


#endif //RAYTRACER_WORLD_HPP
