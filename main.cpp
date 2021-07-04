#include <iostream>
#include <memory>
#include <thread>
#include <algorithm>
#include <functional>
#include <atomic>


#include "Utils/vec3.hpp"
#include "Utils/clocks.hpp"
#include "Utils/ray.hpp"
#include "Objects/sphere.hpp"
#include "Utils/maths.hpp"
#include "Objects/world.hpp"
#include "Utils/camera.hpp"
#include "Utils/color.hpp"


using namespace std;


color ray_color(const ray &r, const hittable &world, int depth) {
    if (depth <= 0)
        return color(0, 0, 0);
    contact contact_data;
    auto is_hit = world.hit(r, 0.001, infinity, contact_data);
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

void write_color_vector(vector<color> &image1) {
    for (auto normalIterator = image1.begin(); normalIterator != image1.end(); ++normalIterator) {
        write_color(cout,*normalIterator);
    }
}

static atomic<int> remainingLines = 0;
int main() {

    //Image
    const auto aspect_ratio = 16.0 / 9.0;
    const int image_width = 500;
    const int image_height = static_cast<int>(image_width / aspect_ratio);
    const int samples_per_pixel = 150;
    const int max_depth = 100;

    //World
    world world = random_scene();

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



vector<color> rayTrace(const int image_width, const int image_height,
                       const int height_start, const int height_end,
                       const int samples_per_pixel, const int max_depth,
                       const world &world, const camera &camera, vector<color> &image) {


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
