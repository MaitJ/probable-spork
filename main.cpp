#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <fstream>
#include "shader.hpp"
#include "window.hpp"
#include <glm/glm.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "utilities/obj.hpp"
#include "utilities/gl_conf.hpp"
#include "entities/renderable_object.hpp"
#include "entities/world_light.hpp"
#include "entities/camera.hpp"
#include "events/event_handler.hpp"

 
int main(void)
{
	//OpenGL gets context from game_window init
	GameWindow game_window;

	Shader default_shader("vertex_shader.vert", "fragment_shader.frag");
    default_shader.layout_len = 8;

	Utilities::setupGl();


	//Unbind buffers
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

    Camera camera;
    glm::vec3 camera_pos = glm::vec3(-25.0f, -175.0f, -200.0f);
    camera.setRotation(glm::radians(30.0f), glm::vec3(1.0f, .0f, .0f));
    camera.setPosition(camera_pos.x, camera_pos.y, camera_pos.z);

    default_shader.setVec3f("camera_pos", camera_pos);

	glm::mat4 persp_proj = glm::perspective(glm::radians(45.0f), (float)1920/(float)1080, 0.1f, 1000.0f);

    WorldLight light;
    light.shader = &default_shader;
    light.setPosition(100.0f, 150.0f, 100.0f);

	RenderableObject chair("assets/chair_textured.obj", "assets/wood.jpg", &persp_proj, &camera.getCameraMat(), &default_shader);
	chair.shader = &default_shader;
	chair.setScale(30.0f, 30.0f, 30.0f);

	RenderableObject plane = Renderables::Primitive<PrimitiveShape::PLANE>();
	plane.shader = &default_shader;
	plane.setScale(100.0f, 100.0f, 100.0f);
	plane.setPos(0.0f, 0.0f, -100.0f);
	plane.setMatrices(&persp_proj, &camera.getCameraMat());

	while (!glfwWindowShouldClose(game_window.window))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		chair.render();
		plane.render();

		glfwSwapBuffers(game_window.window);
		glfwPollEvents();
        EventHandler::pollEvents();
	}
 
	default_shader.close();
	glfwDestroyWindow(game_window.window);
 
	glfwTerminate();
	exit(EXIT_SUCCESS);
	return 0;
}

