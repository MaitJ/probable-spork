#include "engine.hpp"
#include "utilities/gl_conf.hpp"

#include "entities/renderable_object.hpp"
#include "entities/player.hpp"
#include "events/event_handler.hpp"

glm::mat4 Engine::createPerspectiveMatrix(float window_width, float window_height, float fov) {
	return glm::perspective(glm::radians(fov), window_width/window_height, 0.1f, 1000.0f);
}

Engine::Engine(float window_width, float window_height, float fov) : default_shader("vertex_shader.vert", "fragment_shader.frag"), persp_proj{createPerspectiveMatrix(window_width, window_height, fov)}, camera(&this->view_proj) {
    Utilities::setupGl();

    this->default_shader.layout_len = 8;

    this->world_light.shader = &default_shader;
    this->world_light.setPosition(100.0f, 150.0f, 100.0f);

    this->view_proj = persp_proj * camera.getCameraMat();

}



void Engine::start() {

	RenderableObject chair("assets/chair_textured.obj", "assets/wood.jpg", &view_proj, &default_shader);
	chair.setScale(20.0f, 20.0f, 20.0f);
    chair.setPos(20.f, 0.0f, -100.f);
    chair.setOrientation(0.f, .0f, .0f);

    RenderableManager::addRenderable(&chair);

	RenderableObject plane = Renderables::Primitive<PrimitiveShape::PLANE>(&view_proj, &default_shader);
	plane.setScale(500.0f, 500.0f, 500.0f);
	plane.setPos(0.0f, 0.0f, .0f);
    plane.setOrientation(0.f, .0f, .0f);

    RenderableManager::addRenderable(&plane);

    Player test_player(&view_proj, &default_shader);
    test_player.transform.setDimensions(20.f, 20.f, 20.f);



	while (!glfwWindowShouldClose(game_window.window))
	{
        view_proj = persp_proj * camera.getCameraMat();
        //Calculate view_proj
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        RenderableManager::renderObjects();

		glfwSwapBuffers(game_window.window);
		glfwPollEvents();
        EventHandler::pollEvents();
	}

    this->close();

}

void Engine::close() {
	this->default_shader.close();
	glfwDestroyWindow(this->game_window.window);
 
	glfwTerminate();
	exit(EXIT_SUCCESS);
}
