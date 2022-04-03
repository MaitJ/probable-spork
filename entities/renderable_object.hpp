#ifndef RENDERABLE_ENTITY_H
#define RENDERABLE_ENTITY_H

#include "../shader.hpp"
#include <string>
#include <glm/glm.hpp>

enum PrimitiveShape {
	PLANE
};

//Right handed coord system
class RenderableObject {
public:
	void render();
	RenderableObject();
	RenderableObject(std::string obj_file, glm::mat4* proj_mat, glm::mat4* camera_mat);
	void setScale(float x, float y, float z);
	void setPos(float x, float y, float z);
	void setMatrices(glm::mat4* proj_mat, glm::mat4* camera_mat);
	void glBind();

	Shader* shader = nullptr;

	unsigned int total_vertices = 0;

private:
	bool ebo_rendered = false;
	unsigned int vbo, vao, ebo = 0;
	unsigned int total_indices = 0;

	glm::mat4* proj_mat = nullptr;
	glm::mat4* camera_mat = nullptr;
	glm::mat4 scale_mat = glm::mat4(1.0f);
	glm::mat4 pos_mat = glm::mat4(1.0f);

};

namespace Renderables {

	template <PrimitiveShape>
	RenderableObject Primitive();

	template <>
	RenderableObject Primitive<PLANE>();
}

#endif // !RENDERABLE_ENTITY_H
