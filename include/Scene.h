//
// Created by vladimir on 17.02.24.
//

#ifndef RAYTRACING_HW_SCENE_H
#define RAYTRACING_HW_SCENE_H

#include <iostream>
#include <sstream>
#include <fstream>
#include <cmath>
#include <vector>

#include "Position.h"
#include "Primitives.h"

struct Camera {
    Position position;
    Position right;
    Position up;
    Position forward;
    double fov_x;
    double fov_y;
    int width = 100;
    int height = 100;

    void set_fov(double fov_x0) {
        fov_x = fov_x0;
        fov_y = atan(tan(fov_x / 2) * height / width) * 2;
    }

    Ray generate_ray(int x, int y, int ray_depth = 5) const {
        Ray ray;
        ray.depth = ray_depth;
        ray.origin = position;

        double px = (2.0 * x / width - 1)  * tan(fov_x / 2);
        double py = (2.0 * y / height - 1) * tan(fov_y / 2);
        double pz = 1;

        ray.direction = glm::normalize(right * px + up * py + forward * pz);

        return ray;
    }
};

#define COMMAND_DIMENSIONS      0
#define COMMAND_BG_COLOR        1
#define COMMAND_CAMERA_POSITION 2
#define COMMAND_CAMERA_RIGHT    3
#define COMMAND_CAMERA_UP       4
#define COMMAND_CAMERA_FORWARD  5
#define COMMAND_CAMERA_FOV_X    6
#define COMMAND_NEW_PRIMITIVE   7
#define COMMAND_PLANE           8
#define COMMAND_ELLIPSOID       9
#define COMMAND_BOX             10
#define COMMAND_POSITION        11
#define COMMAND_ROTATION        12
#define COMMAND_COLOR           13
#define COMMAND_RAY_DEPTH       14
#define COMMAND_AMBIENT_LIGHT   15
#define COMMAND_NEW_LIGHT       16
#define COMMAND_LIGHT_INTENSITY 17
#define COMMAND_LIGHT_DIRECTION 18
#define COMMAND_LIGHT_POSITION  18
#define COMMAND_LIGHT_ATTENUATION 19
#define COMMAND_METALLIC        20
#define COMMAND_DIELECTRIC      21
#define COMMAND_IOR             22


class Scene {
    Color bg_color = {0, 0, 0.1};
    std::vector<Object*> primitives;
    Camera camera;
    int ray_depth = 5;

public:

    Scene() = default;

    Object*& last_primitive() {
        return primitives.back();
    }

    int getCommand(const std::string& command);
    void load(std::string scene_path);

    Object* intersectObjects(Ray ray);
    Color raytrace(Ray ray);
    std::vector<u_int8_t> render();
    void renderScene(std::string output_path);
};


#endif //RAYTRACING_HW_SCENE_H
