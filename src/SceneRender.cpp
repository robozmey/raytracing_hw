//
// Created by vladimir on 17.02.24.
//

#include "Scene.h"

Color Scene::raytrace(Ray ray) {
    Color pixel_color = bg_color;
    double pixel_t = -1;

    for (const Primitive* primitive : primitives) {
        Ray new_ray = primitive->move(ray);
        double t = primitive->intersection(new_ray);
        if (t > 0 && t < pixel_t || t > 0 && pixel_t < 0) {
            pixel_t = t;
            pixel_color = primitive->get_color();
        }
    }
    return pixel_color;
}

std::vector<u_int8_t> Scene::render() {
    std::vector<u_int8_t> output;
    for (int py = camera.height-1; py >= 0; py--) {
        for (int px = 0; px < camera.width; px++) {
            Ray ray = camera.generate_ray(px + 0.5, py + 0.5);

            Color pixel_color = raytrace(ray);

            output.push_back(b2f(pixel_color.r));
            output.push_back(b2f(pixel_color.g));
            output.push_back(b2f(pixel_color.b));
        }
    }
    return output;
}

void Scene::render_scene(std::string output_path) {

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
