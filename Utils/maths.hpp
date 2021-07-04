//
// Created by axell on 7/4/2021.
//

#ifndef RAYTRACER_MATHS_HPP
#define RAYTRACER_MATHS_HPP
#include<random>

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

inline double degrees_to_radians(double degrees) {
    return degrees * pi / 180.0;
}

inline double clamp(double value, double min, double max){
    if (value < min)
        return min;
    if (value > max)
        return max;
    return value;
}

inline double min(double value1, double value2){
    if (value1 < value2)
        return value1;
    return value2;
}

inline double abs(double value){
    if (value < 0)
        return - value;
    return value;
}
static std::mt19937 generator(time(NULL));


inline double random_double(double min = 0.0, double max = 1.0) {
    std::uniform_real_distribution<double> random(min,max);
    return random(generator);
}

inline vec3 random_vector() {
    return vec3(random_double(-1.0,1.0),random_double(-1.0,1.0),random_double(-1.0,1.0));
}

inline color random_color(){
    return vec3(random_double(),random_double(),random_double());
}

inline vec3 random_unit() {
    while(true){
        auto candidate = random_vector();
        if(candidate.length_squared() < 1)
            return candidate;
    }
}

vec3 random_in_unit_disk() {
    while (true) {
        auto candidate = vec3(random_double(-1,1), random_double(-1,1), 0);
        if(candidate.length_squared() < 1)
            return candidate;
    }
}

inline  bool near_zero(vec3 vec){
    const auto epsilon = 1e-3;
    return vec.length_squared() < epsilon;
}

#endif //RAYTRACER_MATHS_HPP
