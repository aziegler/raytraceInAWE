//
// Created by axell on 7/4/2021.
//

#ifndef RAYTRACER_CAMERA_HPP
#define RAYTRACER_CAMERA_HPP


class camera {
public:
    camera(point3 origin, point3 sceneCenter, vec3 vup, double vfov, double aspect_ratio, double aperture) :
    _origin(origin)
    {
        auto fov_in_rad = degrees_to_radians(vfov);
        auto viewport_height = tan(fov_in_rad/2) * 2;
        auto viewport_width = viewport_height * aspect_ratio;
        auto focus_dist = (sceneCenter - origin).length();

        _w = (origin - sceneCenter).unit_vector();
        _u = cross(vup,_w).unit_vector();
        _v = cross(_w,_u);


        _width_vector = _u * viewport_width * focus_dist;
        _height_vector = _v * viewport_height * focus_dist;
        _viewport_origin = _origin - _width_vector * (1.0/2) - _height_vector * (1.0/2) - _w * focus_dist;

        _lens_radius = aperture / 2;
    }

    ray get_ray(double s, double t) const {
        vec3 dec = random_in_unit_disk() * _lens_radius;
        vec3 offset = _u * dec.x() + _v * dec.y();
        return ray(_origin + offset, _viewport_origin + _width_vector * s + _height_vector * t - _origin - offset);
    }

private:
    point3 _origin;
    point3 _viewport_origin;
    vec3 _width_vector;
    vec3 _height_vector;
    vec3 _u,_v,_w;
    double _lens_radius;
};


#endif //RAYTRACER_CAMERA_HPP
