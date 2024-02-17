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

    Ray generate_ray(int x, int y) const {
        Ray ray;
        ray.origin = position;

        double px = (2.0 * x / width - 1)  * tan(fov_x / 2);
        double py = (2.0 * y / height - 1) * tan(fov_y / 2);
        double pz = 1;

        ray.direction = (right * px + up * py + forward * pz).normalize();

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


class Scene {
    Color bg_color = {0, 0, 0.1};
    std::vector<Primitive*> primitives;
    Camera camera;

public:

    Scene() = default;

    Primitive*& last_primitive() {
        return primitives.back();
    }

    int get_command(const std::string& command);
    void load(std::string scene_path);

    Color raytrace(Ray ray);
    std::vector<u_int8_t> render();
    void render_scene(std::string output_path);
};


#endif //RAYTRACING_HW_SCENE_H
