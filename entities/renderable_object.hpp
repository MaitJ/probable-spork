#ifndef RENDERABLE_ENTITY_H
#define RENDERABLE_ENTITY_H

#include "../shader.hpp"
#include <string>
#include <glm/glm.hpp>
#include "obj.hpp"

enum PrimitiveShape {
	PLANE
};

//Right handed coord system
class RenderableObject {
public:
	void render();
	RenderableObject();
	RenderableObject(std::string obj_file, glm::mat4* proj_mat, glm::mat4* camera_mat, Shader* shader);
	RenderableObject(std::string obj_file, std::string tex_file, glm::mat4* proj_mat, glm::mat4* camera_mat, Shader* shader);
	void setScale(float x, float y, float z);
	void setPos(float x, float y, float z);
    void setOrientation(float x, float y, float z);
	void setMatrices(glm::mat4* proj_mat, glm::mat4* camera_mat);
	void glBind();

	Shader* shader = nullptr;

	unsigned int total_vertices = 0;

private:
    void baseObjSetup(Utilities::Obj* obj, glm::mat4* proj_mat, glm::mat4* camera_mat);

private:
    bool textured = false;
    //Vertex buffer, vertex array, element array, texture object
	unsigned int vbo, vao, ebo, to = 0;

	glm::mat4* proj_mat = nullptr;
	glm::mat4* camera_mat = nullptr;
	glm::mat4 scale_mat = glm::mat4(1.0f);
	glm::mat4 pos_mat = glm::mat4(1.0f);
    glm::vec3 orientation = glm::vec3(1.0f);

};

namespace Renderables {

	template <PrimitiveShape>
	RenderableObject Primitive();

	template <>
	RenderableObject Primitive<PLANE>();
}

#endif // !RENDERABLE_ENTITY_H
