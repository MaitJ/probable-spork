#include "engine.hpp"
#include "utilities/gl_conf.hpp"
#include <functional>
#include "entities/renderable_object.hpp"
#include "entities/player.hpp"
#include "events/event_handler.hpp"
#include "entities/entity.hpp"
#include "collisions/collision_manager.hpp"

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
    camera.setPosition(0.f, 50.f, 0.f);


    this->world_light.shader = default_shader;
    this->world_light.setPosition(100.0f, 150.0f, 100.0f);

    this->view_proj = this->persp_proj * camera.getCameraMat();

    Wireframe::initWireframeModel();
}

void Engine::updateDt(std::chrono::time_point<std::chrono::high_resolution_clock> begin, std::chrono::time_point<std::chrono::high_resolution_clock> end) {
    std::chrono::duration<double> time_span(end - begin);
    auto seconds = std::chrono::duration_cast<std::chrono::duration<double>>(time_span);
    this->dt.set(seconds.count());
}


void Engine::start() {
    using namespace std;
    assert(this->default_shader != nullptr);

    shared_ptr<Entity> chair = ctx.createEntity().lock();
    chair->loadModel("assets/chair_textured.obj", "assets/wood.jpg");
    
	chair->renderable.setScale(20.0f, 20.0f, 20.0f);
    chair->renderable.setPos(20.f, 0.0f, -100.f);
    chair->renderable.setOrientation(0.f, .0f, .0f);

    chair->transform.setPosition(20.f, 0.0f, -100.f);
    chair->transform.setDimensions(25.f, 60.f, 25.f);
    chair->transform.setOrientation(0.f, .0f, .0f);
    chair->enableWireframe();
    //chair.enableCollisions();


    /*
    Entity plane;
    PrimitiveObjects::loadPrimitive<PrimitiveShape::PLANE>(plane);
	plane.transform.setDimensions(500.0f, 500.0f, 500.0f);
	plane.transform.setPosition(0.0f, 0.0f, .0f);
    plane.transform.setOrientation(0.f, .0f, .0f);
    */

    Player test_player(view_proj, default_shader, this->camera, this->ctx);
    test_player.game_ent->transform.setDimensions(20.f, 20.f, 20.f);
    test_player.game_ent->renderable.setScale(20.f, 20.f, 20.f);
    //test_player.game_ent.enableCollisions();
    test_player.game_ent->enableWireframe();



	while (!glfwWindowShouldClose(game_window.window))
    {
        auto f_start = std::chrono::high_resolution_clock::now();
        EventHandler::pollEvents();
        test_player.updateVelocity(this->dt);

        this->camera.recalcMatrix();
        this->view_proj = this->persp_proj * camera.getCameraMat();

        //Calculate view_proj
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        RenderableManager::renderObjects();

		glfwSwapBuffers(game_window.window);
		glfwPollEvents();
        this->updateDt(f_start, std::chrono::high_resolution_clock::now());
    }

    this->close();

}

void Engine::close() {
	this->default_shader->close();
	glfwDestroyWindow(this->game_window.window);
 
	glfwTerminate();
	exit(EXIT_SUCCESS);
}
