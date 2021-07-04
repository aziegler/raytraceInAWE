//
// Created by axell on 7/4/2021.
//

#ifndef RAYTRACER_HITTABLE_LIST_HPP
#define RAYTRACER_HITTABLE_LIST_HPP


#include "hittable.hpp"

#include <memory>
#include <vector>

class hittable_list : public hittable {
public:
    hittable_list() = default;

    hittable_list(std::shared_ptr<hittable> object) { add(object); }

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


#endif //RAYTRACER_HITTABLE_LIST_HPP
