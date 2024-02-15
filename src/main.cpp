#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>
#include <cmath>

class Color {
public:
    float r, g, b;
    void set(float r0, float g0, float b0) {
        r = r0;
        g = g0;
        b = b0;
    }
};

u_int8_t b2f(float c) {
    return round(c * 255);
}

class Position {
public:
    float x, y, z;
    Position() {}
    Position(float x0, float y0, float z0) : x(x0), y(y0), z(z0) {}
    void set(float x0, float y0, float z0) {
        x = x0;
        y = y0;
        z = z0;
    }

    float cross(Position other) {
        return x * other.x + y * other.y + z * other.z;
    }

    Position operator+(Position other) {
        return {x + other.x, y + other.y,  z + other.z};
    }
    Position operator-(Position other) {
        return {x - other.x, y - other.y,  z - other.z};
    }
    Position operator*(Position other) {
        return {x * other.x, y * other.y,  z * other.z};
    }
    Position operator/(Position other) {
        return {x / other.x, y / other.y,  z / other.z};
    }

    Position operator*(float c) {
        return {x * c, y * c, z * c};
    }

    Position normalize() {
        float norm = sqrt(x * x + y * y + z * z);
        return {x / norm, y / norm, z / norm};
    }
};

class Rotation {
public:
    float x, y, z, w;
    void set(float x0, float y0, float z0, float w0) {
        x = x0;
        y = y0;
        z = z0;
        w = w0;
    }
};

class Ray {
public:
    Position origin;
    Position direction;
    Ray() {}
};

class Primitive {
    Position position = {0, 0, 0};
    Rotation rotation = {0, 0, 0, 0};
    Color color = {0, 0, 0};

public:
    Primitive() {}

    Position get_position() const {
        return position;
    }
    void set_position(Position position0) {
        position = position0;
    }

    Rotation get_rotation() const {
        return rotation;
    }
    void set_rotation(Rotation rotation0) {
        rotation = rotation0;
    }

    void set_color(Color color0) {
        color = color0;
    }
    Color get_color() const {
        return color;
    }

    Ray move(Ray ray) const {
        ray.origin = ray.origin - position;
        return ray;
    }

    virtual float intersection(Ray ray) const {
        return -1;
    }
};

class Plane : public Primitive {
public:
    Position normal;
    Plane() = default;
    Plane(Position normal0) : normal(normal0) {}
    float intersection(Ray ray) const override {
        float on = ray.origin.cross(normal);
        float dn = ray.direction.cross(normal);
        if (dn == 0) return -1;
        return - on / dn;
    }
};

class Box : public Primitive {
public:
    Position size;
    Box() = default;
    Box(Position size0) : size(size0) {}
    float intersection(Ray ray) const override  {
        return -1;
    }
};

class Ellipsoid : public Primitive {
public:
    Position size;
    Ellipsoid() = default;
    Ellipsoid(Position size0) : size(size0) {}
    float intersection(Ray ray) const override  {
        float a = (ray.direction / size).cross(ray.direction / size);
        float b = (ray.origin    / size).cross(ray.direction / size) * 2;
        float c = (ray.origin    / size).cross(ray.origin    / size) -1;
        float d = b*b - 4*a*c;
        if (d < 0) return -1;
        float t1 = (-b + sqrt(d)) / (2 * a);
        float t2 = (-b - sqrt(d)) / (2 * a);
        if (t1 < t2 && t1 > 0)
            return t1;
        else
            return t2;
    }
};

struct Camera {
    Position position;
    Position right;
    Position up;
    Position forward;
    float fov_x;
    float fov_y;
    int width;
    int height;

    void set_fov(float fov_x0) {
        fov_x = fov_x0;
        fov_y = atan(tan(fov_x / 2) * height / width) * 2;
    }

    Ray generate_ray(int x, int y) {
        Ray ray;
        ray.origin = position;

        float px = (2.f * x / width - 1)  * tan(fov_x / 2);
        float py = (2.f * y / height - 1) * tan(fov_y / 2);
        float pz = 1;

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
    Color bg_color;
    std::vector<Primitive*> primitives;
    Camera camera;

public:

    Scene() {}

    Primitive*& last_primitive() {
        return primitives.back();
    }

    int get_command(std::string command) {
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

        return -1;
    }

    void load(std::string scene_path) {
        std::ifstream scene_file;
        scene_file.open(scene_path);
        std::string command_str;
        while(!scene_file.eof()) {
            std::string command_line;
            getline(scene_file, command_line);

            std::stringstream ss;
            ss << command_line;
            ss >> command_str;

            int command = get_command(command_str);
            switch (command) {
                case COMMAND_DIMENSIONS: {
                    int w, h;
                    ss >> w >> h;
                    camera.width = w;
                    camera.height = h;
                    break;
                }
                case COMMAND_BG_COLOR: {
                    float r, g, b;
                    ss >> r >> g >> b;
                    bg_color.set(r, g, b);
                    break;
                }
                case COMMAND_CAMERA_FOV_X: {
                    float fov_x;
                    ss >> fov_x;
                    camera.set_fov(fov_x);
                }
                case COMMAND_CAMERA_POSITION:
                case COMMAND_CAMERA_RIGHT:
                case COMMAND_CAMERA_UP:
                case COMMAND_CAMERA_FORWARD: {
                    float x, y, z;
                    ss >> x >> y >> z;

                    switch (command) {
                        case COMMAND_CAMERA_POSITION:
                            camera.position.set(x, y, z);
                            break;
                        case COMMAND_CAMERA_RIGHT:
                            camera.right.set(x, y, z);
                            break;
                        case COMMAND_CAMERA_UP:
                            camera.up.set(x, y, z);
                            break;
                        case COMMAND_CAMERA_FORWARD:
                            camera.forward.set(x, y, z);
                            break;
                    }
                    break;
                }
                case COMMAND_NEW_PRIMITIVE: {
                    primitives.push_back(new Primitive());
                    break;
                }
                case COMMAND_PLANE:
                case COMMAND_ELLIPSOID:
                case COMMAND_BOX: {
                    float x, y, z;
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
                    float x, y, z;
                    ss >> x >> y >> z;
                    last_primitive()->set_position({x, y, z});
                    break;
                }
                case COMMAND_ROTATION: {
                    float x, y, z, w;
                    ss >> x >> y >> z >> w;
                    last_primitive()->set_rotation({x, y, z, w});
                    break;
                }
                case COMMAND_COLOR: {
                    float r, g, b;
                    ss >> r >> g >> b;
                    last_primitive()->set_color({r, g, b});
                    break;
                }
                default: {
                    exit(-1);
                }
            }
        }
        scene_file.close();
    }

    Color raytrace(Ray ray) {
        Color pixel_color = bg_color;
        float pixel_t = -1;

        for (const Primitive* primitive : primitives) {
            Ray new_ray = primitive->move(ray);
            float t = primitive->intersection(new_ray);
            if (t > 0 && t < pixel_t || t > 0 && pixel_t < 0) {
                pixel_t = t;
                pixel_color = primitive->get_color();
            }
        }
        return pixel_color;
    }

    std::vector<u_int8_t> render() {
        std::vector<u_int8_t> output;
        for (int py = camera.height-1; py >= 0; py--) {
            for (int px = 0; px < camera.width; px++) {
                Ray ray = camera.generate_ray(px, py);

                Color pixel_color = raytrace(ray);

                output.push_back(b2f(pixel_color.r));
                output.push_back(b2f(pixel_color.g));
                output.push_back(b2f(pixel_color.b));
            }
        }
        return output;
    }

    void render_scene(std::string output_path) {

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
};

int main(int argc, char *argv[]) {

    std::string scene_path = argv[1];
    std::string output_path = argv[2];

    Scene scene;
    scene.load(scene_path);
    scene.render_scene(output_path);

    return 0;
}
