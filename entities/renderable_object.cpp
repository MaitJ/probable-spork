#include "renderable_object.hpp"
#include "../utilities/obj.hpp"
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

RenderableObject::RenderableObject() {
	glGenVertexArrays(1, &this->vao);
	glGenBuffers(1, &this->vbo);
	glGenBuffers(1, &this->ebo);
}

RenderableObject::RenderableObject(std::string obj_file, glm::mat4* proj_mat, glm::mat4* camera_mat) {
	this->proj_mat = proj_mat;
	this->camera_mat = camera_mat;

	Utilities::Obj* obj = new Utilities::Obj(obj_file);
	this->ebo_rendered = true;

	glGenVertexArrays(1, &this->vao);
	glGenBuffers(1, &this->vbo);
	glGenBuffers(1, &this->ebo);
	glBindVertexArray(this->vao);

	glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
	glBufferData(GL_ARRAY_BUFFER, obj->vertices.size() * sizeof(float), obj->vertices.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, obj->triangles.size() * sizeof(unsigned int), obj->triangles.data(), GL_STATIC_DRAW);

	glm::mat4 chair_model_mat = glm::scale(glm::mat4(1.0f), glm::vec3(30.0f, 30.0f, 30.0f));

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	this->total_indices = obj->triangles.size();

	delete obj;
}

void RenderableObject::setScale(float x, float y, float z) {
	this->scale_mat = glm::scale(glm::mat4(1.0f), glm::vec3(x, y, z));
}
void RenderableObject::setPos(float x, float y, float z) {
	this->pos_mat = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, z));
}

void RenderableObject::glBind() {
	glBindVertexArray(this->vao);
	glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
}
void RenderableObject::setMatrices(glm::mat4* proj_mat, glm::mat4* camera_mat) {
	this->proj_mat = proj_mat;
	this->camera_mat = camera_mat;
}

void RenderableObject::render() {
	assert(this->shader != nullptr);
	assert(this->proj_mat != nullptr);
	assert(this->camera_mat != nullptr);

	assert(this->vbo != 0 && this->vao != 0 && this->ebo != 0);

	this->shader->use();
	int MVPLoc = glGetUniformLocation(this->shader->id, "MVP");
	glm::mat4 MVP = *this->proj_mat * (*this->camera_mat) * this->pos_mat * this->scale_mat;
	glBindVertexArray(this->vao);
	glUniformMatrix4fv(MVPLoc, 1, GL_FALSE, glm::value_ptr(MVP));
	if (ebo_rendered) {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ebo);
		glDrawElements(GL_TRIANGLES, this->total_indices, GL_UNSIGNED_INT, 0);
	}
	else {
		glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
		glDrawArrays(GL_TRIANGLES, 0, this->total_vertices);
	}
}


namespace Renderables {

	template <PrimitiveShape>
	RenderableObject Primitive() { }

	template <>
	RenderableObject Primitive<PLANE>() {
		RenderableObject prim_obj;

		prim_obj.glBind();

		float plane_vertices[] = {
			-1.0f, 0.0f, 1.0f,
			1.0f, 0.0f, 1.0f,
			1.0f, 0.0f, -1.0f,

			-1.0f, 0.0f, 1.0f,
			-1.0f, 0.0f, -1.0f,
			1.0f, 0.0f, -1.0f
		};

		prim_obj.total_vertices = 6;

		glBufferData(GL_ARRAY_BUFFER, sizeof(plane_vertices), plane_vertices, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
		return prim_obj;
	}
}
