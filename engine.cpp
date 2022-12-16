#include "engine.hpp"
#include <functional>
#include "mesh/node.hpp"
#include "entities/entity.hpp"
#include "entities/player.hpp"
#include "utilities/gl_conf.hpp"
#include "events/event_handler.hpp"
#include "entities/primitive_entity_factory.hpp"

Engine::Engine(float window_width, float window_height) :
    game_window(window_width, window_height),
    view_proj(RenderableManager::getViewProjMat()),
    persp_proj(RenderableManager::getPerspectiveMat()),
    camera(RenderableManager::getViewProjMat()) {

    Utilities::setupGl();
    camera.setPosition(0.f, 50.f, 0.f);

    ShaderManager::initializeShaders();

    this->ctx.world_light.setPosition(100.0f, 150.0f, 100.0f);

    this->view_proj = this->persp_proj * camera.getCameraMat();

    // TODO: Replace MainShader::getShader with ShaderManager
    Wireframe::initWireframeModel();
}

void Engine::updateDt(std::chrono::time_point<std::chrono::high_resolution_clock> begin, 
        std::chrono::time_point<std::chrono::high_resolution_clock> end) {
    std::chrono::duration<double> time_span(end - begin);
    auto seconds = std::chrono::duration_cast<std::chrono::duration<double>>(time_span);
    this->dt.set(seconds.count());
}


void Engine::start() {
    using namespace std;

    PrimitiveEntityFactory planeFactory(ctx);
    planeFactory.setShape(PrimitiveShape::PLANE);
    planeFactory.isStatic(false);

    shared_ptr<Entity> plane = planeFactory.make();
    plane->mesh.transform.setDimensions(500.f, 1.f, 500.f);
	plane->transform.setDimensions(500.0f, 1.0f, 500.0f);
	plane->transform.setPosition(0.0f, 0.0f, .0f);
    plane->transform.setOrientation(0.f, .0f, .0f);
    //plane->enableWireframe();

    shared_ptr<Entity> plane2 = planeFactory.make();
    plane2->mesh.transform.setDimensions(500.f, 1.f, 500.f);
    plane2->mesh.transform.setPosition(50, 100, 50);
    plane2->mesh.transform.setOrientation(0, 90, 0);
    plane2->transform.setDimensions(200.f, 1.f, 200.f);
    plane2->transform.setPosition( 50, 100, 50);
    plane2->transform.setOrientation(0, 90, 0);


    Player test_player(view_proj, this->camera, this->ctx);

    test_player.game_ent->transform.setPosition(0.f, 20.f, 0.f);
    test_player.game_ent->transform.setDimensions(20.f, 20.f, 20.f);
    test_player.game_ent->transform.setOrientation(0.f, 0.f, 0.f);
    test_player.game_ent->mesh.transform.setDimensions(20.f, 20.f, 20.f);
    //test_player.game_ent->mesh.transform.setOrientation(0.f, 90.f, 0.f);
    test_player.game_ent->mesh.transform.setPosition(0.f, 0.f, 0.f);
    //test_player.game_ent->enableWireframe();
    test_player.resetCameraPos();

    shared_ptr<Entity> chair_gltf = ctx.createEntity().lock();
    chair_gltf->mesh.loadGLTFModel("assets/chair_w_root.gltf");

    chair_gltf->mesh.transform.setDimensions(10.f, 10.f, 10.f);
    chair_gltf->mesh.transform.setPosition(-5.0f, 0.f, -5.f);
    chair_gltf->mesh.transform.setOrientation(0.f, 90.0f, .0f);

    chair_gltf->transform.setPosition(-5.f, 0.f, -5.f);
    chair_gltf->transform.setDimensions(50.f, 50.f, 50.f);
    chair_gltf->transform.setOrientation(0.f, .0f, .0f);
    //chair_gltf->enableWireframe();

    shared_ptr<Entity> rigged_simple = ctx.createStaticEntity().lock();
    rigged_simple->mesh.loadGLTFModel("assets/RiggedSimple.gltf");
    rigged_simple->mesh.transform.setDimensions(10.f, 10.f, 10.f);
    rigged_simple->mesh.transform.setPosition(25.f, 10.f, 5.f);
    rigged_simple->mesh.transform.setOrientation(0.f, 90.0f, .0f);




	while (!(bool) glfwWindowShouldClose(game_window.window))
    {
        auto f_start = std::chrono::high_resolution_clock::now();
        EventHandler::pollEvents();
        test_player.updateMovement(this->dt);

        this->camera.recalcMatrix();
        this->view_proj = this->persp_proj * camera.getCameraMat();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        RenderableManager::renderObjects(this->ctx, this->view_proj);

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
