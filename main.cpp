#include <iostream>
#include <memory>
#include <thread>
#include <algorithm>
#include <functional>
#include <atomic>


#include "Utils/vec3.hpp"
#include "Utils/clocks.hpp"
#include "ray.hpp"
#include "Objects/sphere.hpp"
#include "Utils/maths.hpp"
#include "Objects/hittable_list.hpp"
#include "camera.hpp"
#include "Materials/diffuseMaterial.hpp"
#include "Materials/metalMaterial.hpp"
#include "Materials/fuzzyMetal.hpp"
#include "Materials/dielectricMaterial.hpp"
#include "Utils/color.hpp"

vector<color> rayTrace(const int image_width, const int image_height, const int height_start, const int height_end, const int samples_per_pixel, const int max_depth,
                       const hittable_list &world, const camera &camera, vector<color> &image);

void write_color_vector(vector<color> &image1);

using namespace std;


color ray_color(const ray &r, const hittable &world, int depth) {
    if (depth <= 0)
        return color(0, 0, 0);
    contact contact_data;
    auto is_hit = world.hit(r, 0.000000001, infinity, contact_data);
    if (!is_hit) {
        vec3 unit_direction = r.getDir().unit_vector();
        auto t = 0.5 * (unit_direction.y() + 1.0);

        return color(1.0, 1.0, 1.0) * (1.0 - t) + color(0.5, 0.7, 1.0) * t;
    } else {
        color attenuated;
        ray next_ray;
        if (contact_data.mat_ptr->scatter(r, contact_data, attenuated, next_ray)) {
            return ray_color(next_ray, world, depth - 1) * attenuated;
        }
        return color(0, 0, 0);
    }
}

hittable_list random_scene() {
    hittable_list world;
    double scene_width = 8;
    double scene_depth = 8;

    auto ground_material = make_shared<diffuseMaterial>(color(0.2, 0.2, 0.2));
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


static atomic<int> remainingLines = 0;

int main() {

    //Image
    const auto aspect_ratio = 16.0 / 9.0;
    const int image_width = 2000;
    const int image_height = static_cast<int>(image_width / aspect_ratio);
    const int samples_per_pixel = 40;
    const int max_depth = 100;

    //World
    hittable_list world = random_scene();

    //Camera
    camera camera(point3(12, 5, 3), point3(0, 0, 0), vec3(0, 1, 0), 30, aspect_ratio, 0.01);




    remainingLines = image_height;
    auto glambda = [=](auto height_start, auto height_end,vector<color> &image){
        rayTrace(image_width,image_height,height_start,height_end,samples_per_pixel,max_depth,world,camera, std::ref(image));
    };

    int sliceCount = 10;
    int sliceSize = image_height / 10;
    std::vector<color> image;
    std::vector<std::vector<color>> images(sliceCount,image);

    std::vector<std::thread>workers;
    for (int i = 0; i < sliceCount; ++i){
        int height = image_height - i* sliceSize;
        int end = (i == sliceCount - 1) ? 0 : image_height - (i + 1) * sliceSize;
        workers.push_back(std::thread (glambda, height, end,std::ref(images[i])));
    }

    std::for_each(workers.begin(),workers.end(),
                  [] (std::thread &t){
        t.join();
        cerr << " Thread joined" << endl;
    });


    perfclock::printRecap();

    int max_value = 255;
    cout << "P3" << endl;
    cout << image_width << " " << image_height << endl;
    cout << max_value << endl;

    std::for_each(images.begin(),images.end(),
                  [] (std::vector<color> &image){
                      write_color_vector(image);
    });

}

void write_color_vector(vector<color> &image1) {
    for (auto normalIterator = image1.begin(); normalIterator != image1.end(); ++normalIterator) {
        write_color(cout,*normalIterator);
    }
}

vector<color> rayTrace(const int image_width, const int image_height,
                       const int height_start, const int height_end,
                       const int samples_per_pixel, const int max_depth,
                       const hittable_list &world, const camera &camera, vector<color> &image) {


    for (int j = height_start - 1; j >= height_end; --j) {
        for (int i = 0; i < image_width; ++i) {
            perfclock::startLog("mainCompute");
            auto u = double(i) / image_width;
            auto v = double(j) / image_height;
            color pixel = ray_color(camera.get_ray(u, v), world, max_depth);
            for (int s = 0; s < (samples_per_pixel - 1); ++s) {
                auto u = (double(i) + random_double()) / image_width;
                auto v = (double(j) + random_double()) / image_height;
                const ray &r = camera.get_ray(u, v);
                pixel += ray_color(r, world, max_depth);
            }
            pixel *= (1.0 / double(samples_per_pixel));
            image.push_back(pixel);
            perfclock::stopLog("mainCompute");
        }
        remainingLines --;
        std::cerr << "\rLines Remaining: " << remainingLines << ' ' << std::flush;
    }
    return image;
}
