cmake_minimum_required(VERSION 3.19)
project(RayTracer)
set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0")

set(CMAKE_CXX_STANDARD 17)

add_executable(RayTracer main.cpp Utils/vec3.hpp Utils/color.hpp Utils/ray.hpp Objects/hittable.hpp Objects/sphere.hpp Objects/world.hpp Utils/maths.hpp Utils/camera.hpp Materials/material.hpp Materials/diffuseMaterial.hpp Materials/metalMaterial.hpp Materials/fuzzyMetal.hpp Materials/dielectricMaterial.hpp Utils/clocks.hpp)
