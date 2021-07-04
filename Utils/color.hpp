//
// Created by axell on 7/4/2021.
//

#ifndef RAYTRACER_COLOR_HPP
#define RAYTRACER_COLOR_HPP

#include <iostream>

void write_color(std::ostream &out, color pixel) {
    double r = sqrt(pixel.x());
    double g = sqrt(pixel.y());
    double b = sqrt(pixel.z());


    out << static_cast<int>(255 * r) << ' '
        << static_cast<int>(255 * g) << ' '
        << static_cast<int>(255 * b) << '\n';
}

#endif //RAYTRACER_COLOR_HPP
