#include "engine.hpp"
#include "utilities/gl_conf.hpp"
#include <functional>
#include "entities/renderable_object.hpp"
#include "entities/player.hpp"
#include "events/event_handler.hpp"
#include "entities/entity.hpp"

#define VERTEX_SHADER_FILE "vertex_shader.vert"
#define FRAGMENT_SHADER_FILE "fragment_shader.frag"
#define WF_VERTEX_SHADER_FILE "wf_vertex_shader.vert"
#define WF_FRAGMENT_SHADER_FILE "wf_fragment_shader.frag"

glm::mat4 Engine::createPerspectiveMatrix(float window_width, float window_height, float fov) {
	return glm::perspective(glm::radians(fov), window_width/window_height, 0.1f, 1000.0f);
}

Engine::Engine(float window_width, float window_height, float fov) : default_shader(MainShaders::loadDefaultShader()), view_proj(RenderableManager::getViewProjMat()), persp_proj(RenderableManager::getPerspectiveMat()), camera(RenderableManager::getViewProjMat()) {
    //assert(this->view_proj != nullptr);
    Utilities::setupGl();


    this->world_light.shader = default_shader;
    this->world_light.setPosition(100.0f, 150.0f, 100.0f);

    this->view_proj = this->persp_proj * camera.getCameraMat();

    Wireframe::initWireframeModel();
}



void Engine::start() {
    assert(this->default_shader != nullptr);

    Entity chair;
    chair.loadModel("assets/chair_textured.obj", "assets/wood.jpg");
	chair.transform.setDimensions(20.0f, 20.0f, 20.0f);
    chair.transform.setPosition(20.f, 0.0f, -100.f);
    chair.transform.setOrientation(0.f, .0f, .0f);
    chair.enableWireframe();


    Entity plane;
    PrimitiveObjects::loadPrimitive<PrimitiveShape::PLANE>(plane);
	plane.transform.setDimensions(500.0f, 500.0f, 500.0f);
	plane.transform.setPosition(0.0f, 0.0f, .0f);
    plane.transform.setOrientation(0.f, .0f, .0f);

    Player test_player(view_proj, default_shader);
    test_player.game_ent.transform.setDimensions(20.f, 20.f, 20.f);
    test_player.game_ent.enableWireframe();



	while (!glfwWindowShouldClose(game_window.window))
    {
        this->view_proj = this->persp_proj * camera.getCameraMat();

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
	this->default_shader->close();
	glfwDestroyWindow(this->game_window.window);
 
	glfwTerminate();
	exit(EXIT_SUCCESS);
}
