#include "renderable_object.hpp"
#include "../utilities/obj.hpp"
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "../deps/stb_image.h"

RenderableObject::RenderableObject() {
	glGenVertexArrays(1, &this->vao);
	glGenBuffers(1, &this->vbo);
	glGenBuffers(1, &this->ebo);
}

void RenderableObject::baseObjSetup(Utilities::Obj* obj) {
    calcModel();
    assert(this->shader != nullptr);
    
    assert(this->shader->layout_len > 0);

	glGenVertexArrays(1, &this->vao);
	glGenBuffers(1, &this->vbo);
	glGenBuffers(1, &this->ebo);
	glBindVertexArray(this->vao);

	glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
	glBufferData(GL_ARRAY_BUFFER, obj->triangles.size() * sizeof(float), obj->triangles.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, this->shader->layout_len * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

    glGenTextures(1, &this->to);
    glBindTexture(GL_TEXTURE_2D, this->to);

    //First have to bind texture object
    //If image isn't big enough
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

    //Setup a mipmap
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, this->shader->layout_len * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, this->shader->layout_len * sizeof(float), (void*)(5 * sizeof(float)));
    glEnableVertexAttribArray(2);
    

    this->total_vertices = obj->total_vertices;

}

RenderableObject::RenderableObject(std::string obj_file, glm::mat4* view_proj, Shader* shader) {
    Utilities::Obj* obj = new Utilities::Obj(obj_file);
    this->view_proj = view_proj;
    this->shader = shader;
    this->baseObjSetup(obj);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
    delete obj;
}

RenderableObject::RenderableObject(std::string obj_file, std::string tex_file, glm::mat4* view_proj, Shader* shader) {
    Utilities::Obj* obj = new Utilities::Obj(obj_file);
    this->view_proj = view_proj;
    this->shader = shader;
    this->baseObjSetup(obj);

    int tex_width, tex_height, tex_nrchannels;
    unsigned char* img_data = stbi_load(tex_file.c_str(), &tex_width, &tex_height, &tex_nrchannels, 0);

    if (!img_data) {
        std::cerr << "Couldn't open image file" << std::endl;
        return;
    }
    this->textured = true;
    
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, tex_width, tex_height, 0, GL_RGB, GL_UNSIGNED_BYTE, img_data);
    glGenerateMipmap(GL_TEXTURE_2D);

    //Shader has is_textured uniform!!!
    //
    stbi_image_free(img_data);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
    delete obj;
}

void RenderableObject::setScale(float x, float y, float z) {
	this->scale_mat = glm::scale(glm::mat4(1.0f), glm::vec3(x, y, z));
    calcModel();
}
void RenderableObject::setPos(float x, float y, float z) {
	this->pos_mat = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, z));
    calcModel();
}

void RenderableObject::calcModel() {
    this->model_mat = this->pos_mat * this->scale_mat * glm::toMat4(this->orientation);
}

void RenderableObject::setOrientation(float x, float y, float z) {
    glm::quat x_rot = glm::angleAxis(glm::radians(x), glm::vec3(1.f, .0f, .0f));
    glm::quat y_rot = glm::angleAxis(glm::radians(y), glm::vec3(0.f, 1.f, .0f));
    glm::quat z_rot = glm::angleAxis(glm::radians(z), glm::vec3(0.f, .0f, 1.f));

    this->orientation = x_rot * y_rot * z_rot;
    calcModel();
}

void RenderableObject::glBind() {
	glBindVertexArray(this->vao);
	glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
}

void RenderableObject::render() {
	assert(this->shader != nullptr);
	assert(this->view_proj != nullptr);

	assert(this->vbo != 0 && this->vao != 0 && this->ebo != 0);

	this->shader->use();
    int model_loc = glGetUniformLocation(this->shader->id, "Model");
	glUniformMatrix4fv(model_loc, 1, GL_FALSE, glm::value_ptr(this->model_mat));

    glm::mat3 normal_mat = glm::transpose(glm::inverse(this->model_mat));
    int normal_mat_loc = glGetUniformLocation(this->shader->id, "normal_mat");
	glUniformMatrix3fv(normal_mat_loc, 1, GL_FALSE, glm::value_ptr(normal_mat));

	int MVPLoc = glGetUniformLocation(this->shader->id, "MVP");
	glm::mat4 MVP = *this->view_proj * model_mat;
	int textured_loc = glGetUniformLocation(this->shader->id, "is_textured");
	glBindVertexArray(this->vao);
    glBindTexture(GL_TEXTURE_2D, this->to);
	glUniformMatrix4fv(MVPLoc, 1, GL_FALSE, glm::value_ptr(MVP));
    glUniform1i(textured_loc, this->textured);
    glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
    glDrawArrays(GL_TRIANGLES, 0, this->total_vertices);
}


namespace Renderables {

	template <PrimitiveShape>
	RenderableObject Primitive(glm::mat4* view_proj);

	template <>
	RenderableObject Primitive<PLANE>(glm::mat4* view_proj) {
		RenderableObject prim_obj;

		prim_obj.glBind();

        prim_obj.view_proj = view_proj;
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
