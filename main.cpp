#include "engine.hpp"

#define TINYGLTF_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <tiny_gltf.h>

#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080
#define FOV 90
 
int main(void) {

    RenderableManager::initPerspectiveMatrix(WINDOW_WIDTH, WINDOW_HEIGHT, FOV);
    Engine engine(WINDOW_WIDTH, WINDOW_HEIGHT);
    engine.start();
    return 0;

}

