//
// Created by vladimir on 17.02.24.
//

#include "Scene.h"

Object* Scene::intersectObjects(Ray ray) {
    double pixel_t = -1;
    Object* res = nullptr;

    for (Object* object : primitives) {
        Ray new_ray = object->move(ray);
        double t = object->intersection(new_ray);
        if (t > 0 && t < pixel_t || t > 0 && pixel_t < 0) {
            pixel_t = t;
            res = object;
        }
    }

    return res;
}

Color Scene::raytrace(Ray ray) {
    Color pixel_color = bg_color;

    Object* nearestIntersection = intersectObjects(ray);

    if (nearestIntersection == nullptr)  return bg_color;

    return nearestIntersection->get_color();
}

std::vector<u_int8_t> Scene::render() {
    std::vector<u_int8_t> output;
    for (int py = camera.height-1; py >= 0; py--) {
        for (int px = 0; px < camera.width; px++) {
            Ray ray = camera.generate_ray(px + 0.5, py + 0.5, ray_depth);

            Color pixel_color = raytrace(ray);

            output.push_back(b2f(pixel_color.r));
            output.push_back(b2f(pixel_color.g));
            output.push_back(b2f(pixel_color.b));
        }
    }
    return output;
}

void Scene::renderScene(std::string output_path) {

    std::vector<u_int8_t> output_binary = render();

    std::ofstream output_file;
    output_file.open(output_path);

    output_file << "P6" << std::endl;
    output_file << camera.width << " " << camera.height << std::endl;
    output_file << 255 << std::endl;

    for (auto v : output_binary) {
        output_file << v;
    }

    output_file.close();

}
