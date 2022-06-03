#include "engine.hpp"
#include "utilities/gl_conf.hpp"
#include <functional>
#include "entities/node.hpp"
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

Engine::Engine(float window_width, float window_height, float fov) : view_proj(RenderableManager::getViewProjMat()), persp_proj(RenderableManager::getPerspectiveMat()), camera(RenderableManager::getViewProjMat()) {
    //assert(this->view_proj != nullptr);
    Utilities::setupGl();
    camera.setPosition(0.f, 50.f, 0.f);

    this->initializeShaders();


    Shader const& textured_shader = this->shader_manager.getShader("textured");
    this->world_light.shader = &textured_shader;
    this->world_light.setPosition(100.0f, 150.0f, 100.0f);

    this->view_proj = this->persp_proj * camera.getCameraMat();

    RenderableManager::setShaderManager(&this->shader_manager);

    // TODO: Replace MainShader::getShader with ShaderManager
    Wireframe::initWireframeModel(this->shader_manager);
}

void Engine::updateDt(std::chrono::time_point<std::chrono::high_resolution_clock> begin, std::chrono::time_point<std::chrono::high_resolution_clock> end) {
    std::chrono::duration<double> time_span(end - begin);
    auto seconds = std::chrono::duration_cast<std::chrono::duration<double>>(time_span);
    this->dt.set(seconds.count());
}


void Engine::start() {
    using namespace std;


    shared_ptr<Entity> plane = ctx.createEntity().lock();
    PrimitiveObjects::loadPrimitive<PrimitiveShape::PLANE>(*plane);
    plane->renderable.shader = &this->shader_manager.getShader("textured");
	plane->transform.setDimensions(500.0f, 1.0f, 500.0f);
	plane->transform.setPosition(0.0f, 0.0f, .0f);
    plane->transform.setOrientation(0.f, .0f, .0f);
    plane->enableWireframe();

    Player test_player(view_proj, this->camera, this->ctx, this->shader_manager);
    test_player.game_ent->transform.setPosition(0.f, 20.f, 0.f);
    test_player.game_ent->transform.setDimensions(20.f, 20.f, 20.f);
    test_player.game_ent->transform.setOrientation(0.f, 0.f, 0.f);
    test_player.game_ent->renderable.setScale(20.f, 20.f, 20.f);
    //test_player.game_ent.enableCollisions();
    test_player.game_ent->enableWireframe();
    test_player.resetCameraPos();

    shared_ptr<Entity> chair_gltf = ctx.createEntity().lock();
    chair_gltf->renderable.shader = &this->shader_manager.getShader("textured");
    chair_gltf->renderable.loadGLTFModel("assets/chair.gltf");
    chair_gltf->renderable.setScale(10.f, 10.f, 10.f);
    chair_gltf->renderable.setPos(-25.0f, 0.f, -50.f);
    chair_gltf->renderable.setOrientation(0.f, .0f, .0f);

    chair_gltf->transform.setPosition(-25.f, 0.f, -50.f);
    chair_gltf->transform.setDimensions(50.f, 50.f, 50.f);
    chair_gltf->transform.setOrientation(0.f, .0f, .0f);
    chair_gltf->enableWireframe();




	while (!glfwWindowShouldClose(game_window.window))
    {
        auto f_start = std::chrono::high_resolution_clock::now();
        EventHandler::pollEvents();
        test_player.updateMovement(this->dt);

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
	glfwDestroyWindow(this->game_window.window);
 
	glfwTerminate();
	exit(EXIT_SUCCESS);
}

void Engine::initializeShaders() {
    std::vector<std::string> shader_names = {"textured", "wireframe"};
    std::vector<std::string> vertex_shader_files = {"vertex_shader.vert", "wf_vertex_shader.vert"};
    std::vector<std::string> fragment_shader_files = {"fragment_shader_mod.frag", "wf_fragment_shader.frag"};

    for (int i = 0; i < shader_names.size(); ++i) {
        Shader shader;
        shader.loadAndCompile(vertex_shader_files[i], fragment_shader_files[i], shader_names[i]);

        this->shader_manager.addShader(shader);
    }

}
