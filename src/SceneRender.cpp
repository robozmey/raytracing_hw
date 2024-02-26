//
// Created by vladimir on 17.02.24.
//

#include "Scene.h"

#define EPS 0.0000001

Object* Scene::intersectObjects(Ray ray) {
    double pixel_t = -1;
    Object* res = nullptr;

    for (Object* object : primitives) {
        double t = object->getDistanceT(ray);
        if (t < EPS) t = -1;
        if (t > 0 && t < pixel_t || t > 0 && pixel_t < 0) {
            pixel_t = t;
            res = object;
        }
    }

    return res;
}

Position getReflection(Position normal, Position direction) {
    return direction - 2.0 * normal * glm::dot(normal, direction);
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

            Position point2 = ray.getPoint(nearest->getDistanceT(ray));
            Object* nearest2 = intersectObjects({point2, direction, 0});
            double neares2_distance = -1, light_distance = -1;
            if (nearest2 != nullptr) neares2_distance = glm::distance(nearest2->get_position(), point);
            if (light->type == PositionalLight) light_distance = glm::distance(light->position, point);

            if (light_distance < neares2_distance) continue;

            double d = glm::dot(normal, direction);
            if (d > 0) {
                double c = light->getCoefficient(point);
                summary_light_color += c * d * light->intensity;
            }
        }
    }
    if (nearest->material.type == MetallicType) {
        Position normal = nearest->getNormal(ray);

        Position reflected_direction = getReflection(normal, ray.direction);
        summary_light_color = raytrace({point, reflected_direction, ray.depth-1});
    }
    if (nearest->material.type == DielectricType) {
        Position normal = nearest->getNormal(ray);

        double n1 = 1, n2 = nearest->material.ior;
        if (ray.is_inside_ray) n1 = nearest->material.ior, n2 = 1;
        Position reflected_direction = getReflection(normal, ray.direction);

        Position l = -ray.direction;
        double cos1 = glm::dot(normal, l);
        double sin2 = n1 / n2 * sqrt(1 - cos1 * cos1);
        double cos2 = sqrt(1 - sin2 * sin2);
        Position refracted_direction = n1 / n2 * (-l) + (n1 / n2 * cos1 - cos2) * normal;

        Color reflected_light_color = raytrace({point, reflected_direction, ray.depth-1, ray.is_inside_ray});
        Color refracted_light_color = raytrace({point, refracted_direction, ray.depth-1, !ray.is_inside_ray});

        double r0 = pow((n1 - n2) / (n1 + n2), 2.0);
        double r  = r0 + (1 - r0) * pow(1 - glm::dot(normal, -ray.direction), 5);
        if (sin2 > 1) {
            summary_light_color = reflected_light_color;
        } else {
            summary_light_color = (reflected_light_color * r + refracted_light_color * (1 - r)) * 1;
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
