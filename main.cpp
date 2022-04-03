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

 
int main(void)
{
	//OpenGL gets context from game_window init
	GameWindow game_window;

	Shader default_shader("vertex_shader.vert", "fragment_shader.frag");

	Utilities::setupGl();


	//Unbind buffers
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	glm::mat4 camera_mat = glm::mat4(1.0f);
	camera_mat = glm::rotate(camera_mat, glm::radians(30.0f), glm::vec3(1.0f, .0f, .0f));
	camera_mat = glm::translate(camera_mat, glm::vec3(-50.0f, -200.0f, -250.0f));

	glm::mat4 persp_proj = glm::perspective(glm::radians(45.0f), (float)1920/(float)1080, 0.1f, 1000.0f);

	RenderableObject chair("assets/chair.obj", &persp_proj, &camera_mat);
	chair.shader = &default_shader;
	chair.setScale(30.0f, 30.0f, 30.0f);

	RenderableObject plane = Renderables::Primitive<PrimitiveShape::PLANE>();
	plane.shader = &default_shader;
	plane.setScale(100.0f, 100.0f, 100.0f);
	plane.setPos(0.0f, 0.0f, -100.0f);
	plane.setMatrices(&persp_proj, &camera_mat);

	while (!glfwWindowShouldClose(game_window.window))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		chair.render();
		plane.render();

		glfwSwapBuffers(game_window.window);
		glfwPollEvents();
	}
 
	default_shader.close();
	glfwDestroyWindow(game_window.window);
 
	glfwTerminate();
	exit(EXIT_SUCCESS);
	return 0;
}

