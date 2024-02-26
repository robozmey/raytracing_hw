//
// Created by vladimir on 17.02.24.
//

#include "Scene.h"

Object* Scene::intersectObjects(Ray ray) {
    double pixel_t = -1;
    Object* res = nullptr;

    for (Object* object : primitives) {
        double t = object->getDistanceT(ray);
        if (t > 0 && t < pixel_t || t > 0 && pixel_t < 0) {
            pixel_t = t;
            res = object;
        }
    }

    return res;
}

Color Scene::raytrace(Ray ray) {
    if (ray.depth == 0) return bg_color;

    Object* nearest = intersectObjects(ray);
    if (nearest == nullptr) return bg_color;
    double t = nearest->getDistanceT(ray);
    Position point = ray.getPoint(t);

    Color summary_light_color = ambient_color;

    if (nearest->material.type == DiffuseType) {
        Position normal = nearest->getNormal(ray);
        for (Light* light : lights) {
            Position direction = light->getDirection(point);
            double d = glm::dot(normal, direction);
            if (d > 0) {
                double c = light->getCoefficient(point);
                summary_light_color += c * d * light->intensity;
            }
        }
    }

    return summary_light_color * nearest->get_color();
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
