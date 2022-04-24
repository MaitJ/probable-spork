#include "engine.hpp"

#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080
#define FOV 90
 
int main(void)
{
    
    RenderableManager::initPerspectiveMatrix(WINDOW_WIDTH, WINDOW_HEIGHT, FOV);
    Engine engine(1920, 1080, 90);
    engine.start();

	return 0;
}

