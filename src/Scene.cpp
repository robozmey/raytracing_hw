//
// Created by vladimir on 17.02.24.
//

#include "Scene.h"

int Scene::getCommand(const std::string& command) {
    if (command == "DIMENSIONS") return COMMAND_DIMENSIONS;
    if (command == "BG_COLOR") return COMMAND_BG_COLOR;
    if (command == "CAMERA_POSITION") return COMMAND_CAMERA_POSITION;
    if (command == "CAMERA_RIGHT") return COMMAND_CAMERA_RIGHT;
    if (command == "CAMERA_UP") return COMMAND_CAMERA_UP;
    if (command == "CAMERA_FORWARD") return COMMAND_CAMERA_FORWARD;
    if (command == "CAMERA_FOV_X") return COMMAND_CAMERA_FOV_X;
    if (command == "NEW_PRIMITIVE") return COMMAND_NEW_PRIMITIVE;
    if (command == "PLANE") return COMMAND_PLANE;
    if (command == "ELLIPSOID") return COMMAND_ELLIPSOID;
    if (command == "BOX") return COMMAND_BOX;
    if (command == "POSITION") return COMMAND_POSITION;
    if (command == "ROTATION") return COMMAND_ROTATION;
    if (command == "COLOR") return COMMAND_COLOR;

    if (command == "RAY_DEPTH") return COMMAND_RAY_DEPTH;
    if (command == "AMBIENT_LIGHT") return COMMAND_AMBIENT_LIGHT;
    if (command == "NEW_LIGHT") return COMMAND_NEW_LIGHT;
    if (command == "LIGHT_INTENSITY") return COMMAND_LIGHT_INTENSITY;
    if (command == "LIGHT_DIRECTION") return COMMAND_LIGHT_DIRECTION;
    if (command == "LIGHT_POSITION") return COMMAND_LIGHT_POSITION;
    if (command == "LIGHT_ATTENUATION") return COMMAND_LIGHT_ATTENUATION;

    if (command == "METALLIC") return COMMAND_METALLIC;
    if (command == "DIELECTRIC") return COMMAND_DIELECTRIC;
    if (command == "IOR") return COMMAND_IOR;


    return -1;
}

void Scene::load(std::string scene_path) {
    std::ifstream scene_file;
    scene_file.open(scene_path);
    std::string command_str;
    while(!scene_file.eof()) {
        std::string command_line;
        getline(scene_file, command_line);

        std::stringstream ss;
        ss << command_line;
        ss >> command_str;

        int command = getCommand(command_str);
        switch (command) {
            case COMMAND_DIMENSIONS: {
                int w, h;
                ss >> w >> h;
                camera.width = w;
                camera.height = h;
                break;
            }
            case COMMAND_RAY_DEPTH: {
                int depth;
                ss >> depth;
                ray_depth = depth;
                break;
            }
            case COMMAND_BG_COLOR: {
                double r, g, b;
                ss >> r >> g >> b;
                bg_color.set(r, g, b);
                break;
            }
            case COMMAND_CAMERA_FOV_X: {
                double fov_x;
                ss >> fov_x;
                camera.set_fov(fov_x);
            }
            case COMMAND_CAMERA_POSITION:
            case COMMAND_CAMERA_RIGHT:
            case COMMAND_CAMERA_UP:
            case COMMAND_CAMERA_FORWARD: {
                double x, y, z;
                ss >> x >> y >> z;

                switch (command) {
                    case COMMAND_CAMERA_POSITION:
                        camera.position = {x, y, z};
                        break;
                    case COMMAND_CAMERA_RIGHT:
                        camera.right = {x, y, z};
                        break;
                    case COMMAND_CAMERA_UP:
                        camera.up = {x, y, z};
                        break;
                    case COMMAND_CAMERA_FORWARD:
                        camera.forward = {x, y, z};
                        break;
                }
                break;
            }
// Objects
            case COMMAND_NEW_PRIMITIVE: {
                primitives.push_back(new Object());
                break;
            }
            case COMMAND_PLANE:
            case COMMAND_ELLIPSOID:
            case COMMAND_BOX: {
                double x, y, z;
                ss >> x >> y >> z;

                switch (command) {
                    case COMMAND_PLANE:
                        delete last_primitive();
                        last_primitive() = new Plane({x, y, z});
                        break;
                    case COMMAND_ELLIPSOID:
                        delete last_primitive();
                        last_primitive() = new Ellipsoid({x, y, z});
                        break;
                    case COMMAND_BOX:
                        delete last_primitive();
                        last_primitive() = new Box({x, y, z});
                        break;
                }
                break;
            }
            case COMMAND_POSITION: {
                double x, y, z;
                ss >> x >> y >> z;
                last_primitive()->set_position({x, y, z});
                break;
            }
            case COMMAND_ROTATION: {
                double x, y, z, w;
                ss >> x >> y >> z >> w;
                last_primitive()->set_rotation({w, x, y, z});
                break;
            }
            case COMMAND_COLOR: {
                double r, g, b;
                ss >> r >> g >> b;
                last_primitive()->set_color({r, g, b});
                break;
            }
// Materials
            case COMMAND_METALLIC:
                last_primitive()->material.type = MetallicType;
                break;
            case COMMAND_DIELECTRIC:
                last_primitive()->material.type = DielectricType;
                break;
            case COMMAND_IOR: {
                double ior;
                ss >> ior;
                last_primitive()->material.ior = ior;
                break;
            }
// Light
            case COMMAND_AMBIENT_LIGHT: {
                double r, g, b;
                ss >> r >> g >> b;
                ambient_color = {r, g, b};
                break;
            }
            case COMMAND_NEW_LIGHT: {
                lights.push_back(new Light());
                break;
            }
            case COMMAND_LIGHT_DIRECTION: {
                double x, y, z;
                ss >> x >> y >> z;
                last_light() = new Light();
                last_light()->direction = {x, y, z};
                last_light()->type = DirectionalLight;
                break;
            }
            case COMMAND_LIGHT_POSITION: {
                double x, y, z;
                ss >> x >> y >> z;
                last_light() = new Light();
                last_light()->position = {x, y, z};
                last_light()->type = PositionalLight;
                break;
            }
            case COMMAND_LIGHT_INTENSITY: {
                double r, g, b;
                ss >> r >> g >> b;
                last_light()->intensity = {r, g, b};
                break;
            }
            case COMMAND_LIGHT_ATTENUATION: {
                double c0, c1, c2;
                ss >> c0 >> c1 >> c2;
                last_light()->attenuation = {c0, c1, c2};
                break;
            }
            default: {
                std::cerr << "Found unknown command: " << command_str << std::endl;
                break;
            }
        }
    }
    scene_file.close();
}
