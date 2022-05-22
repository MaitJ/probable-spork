#include "engine.hpp"

#define TINYGLTF_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <fmt/core.h>
#include "utilities/gltf_loader.hpp"

#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080
#define FOV 90
 
int main(void) {
    bool loaded;
    GLTFLoader jonesy("assets/Jonesy_2.gltf", loaded);

    if (!loaded) {
        fmt::print("[ERROR!] Failed to load model\n");
        return -1;
    }

    std::vector<float> vertex_data = jonesy.getMeshVertexData();


    RenderableManager::initPerspectiveMatrix(WINDOW_WIDTH, WINDOW_HEIGHT, FOV);
    Engine engine(1920, 1080, 90);
    engine.start();

	return 0;
}

