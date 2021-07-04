//
// Created by axell on 7/4/2021.
//

#ifndef RAYTRACER_SPHERE_HPP
#define RAYTRACER_SPHERE_HPP

#include "hittable.hpp"

class sphere : public hittable {
public:
    sphere() {};

    sphere(point3 cen, double r, std::shared_ptr<material> m) : _center(cen), _radius(r), _mat(m) {};

    virtual bool hit(const ray &r, double t_min, double t_max, contact &rec) const override;

private:
    point3 _center;
    double _radius;

    std::shared_ptr <material> _mat;
};

bool sphere::hit(const ray &r, double t_min, double t_max, contact &rec) const {
    const vec3 direct = r.getOrig() - _center;
    vec3 rayDir = r.getDir();
    auto a = rayDir.length_squared();
    auto half_b = dot(direct, rayDir);
    auto c = direct.length_squared() - _radius * _radius;
    auto disc = half_b * half_b - c * a;
    if (disc < 0)
        return false;


    double sqrtDisc = sqrt(disc);
    double t = (-half_b - sqrtDisc) / a;
    if (t < t_min || t > t_max) {
        t = (sqrt(disc) - half_b) / a;
        if (t < t_min or t > t_max) {
            return false;
        }
    }
    rec.t = t;
    rec.p = r.at(t);
    vec3 outward_normal = (rec.p - _center).unit_vector();
    rec.set_face_normal(r, outward_normal);
    rec.mat_ptr = _mat;
    return true;

}


#endif //RAYTRACER_SPHERE_HPP
