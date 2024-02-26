#include "Scene.h"

int main(int argc, char *argv[]) {

    std::string scene_path = argv[1];
    std::string output_path = argv[2];

    Scene scene;
    scene.load(scene_path);
    scene.renderScene(output_path);

    return 0;
}
