#include "node.hpp"
#include "../utilities/obj.hpp"
#include <glm/ext/matrix_transform.hpp>
#include "renderable_manager.hpp"
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>
#include <fmt/core.h>
#include "../utilities/gltf_loader.hpp"
#include <iostream>

//#define STB_IMAGE_IMPLEMENTATION
#include "../deps/stb_image.h"

Node::Node() : view_proj(RenderableManager::getViewProjMat()) {}

Node::Node(ShaderManager &shader_manager, std::string shader_name) : shader(&shader_manager.getShader(shader_name)), view_proj(RenderableManager::getViewProjMat()) {}

void Node::genBuffers() {
    glGenVertexArrays(1, &this->vao);
    glGenBuffers(1, &this->vbo);
    glGenBuffers(1, &this->ebo);
}

template <typename T>
unsigned int sumOfVerticesBytes(std::vector<Mesh> const& meshes) {
    unsigned int sum = 0;
    for (int i = 0; i < meshes.size(); ++i) {
        sum += meshes[i].vertex_data.size() * sizeof(T);
    }
    return sum;
}

void Node::loadGLTFModel(const std::string& file_name) {
    bool loaded;
    GLTFLoader model(file_name, loaded);

    std::vector<Mesh> meshes = model.getMeshes();

    glGenVertexArrays(1, &this->vao);
    glGenBuffers(1, &this->vbo);
    glGenBuffers(1, &this->ebo);

    this->tos = new unsigned int[meshes.size()];
    glGenBuffers(meshes.size(), this->tos);
    this->texture_count = meshes.size();

    this->primitives_count = meshes.size();

    this->primitive_offsets = new unsigned int[meshes.size()];
    this->primitive_offsets[0] = 0;

    glBindVertexArray(this->vao);
    glBindBuffer(GL_ARRAY_BUFFER, this->vbo);

    unsigned int total_vertice_bytes = sumOfVerticesBytes<float>(meshes);
    glBufferData(GL_ARRAY_BUFFER, total_vertice_bytes, nullptr, GL_STATIC_DRAW);

    for (int i = 0; i < meshes.size(); ++i) {
        //! Probably goes out of bounds
        this->primitive_offsets[i + 1] = this->primitive_offsets[i] + meshes[i].vertices;

        //Need to use glBufferSubData, because this overwrites the buffer
        //Instead I need to append to buffer, inorder to keep previous vertex data
        //The 8 is the data size in the shader, so pos vec3 + tex vec2 + normals vec3 3 + 2 + 3 = 8
        glBufferSubData(GL_ARRAY_BUFFER, this->primitive_offsets[i] * 8 * sizeof(float), meshes[i].vertex_data.size() * sizeof(float), meshes[i].vertex_data.data());
        //glBufferData(GL_ARRAY_BUFFER, meshes[i].vertex_data.size() * sizeof(float), meshes[i].vertex_data.data(), GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(5 * sizeof(float)));
        glEnableVertexAttribArray(2);

        loadGLTFTexture(i, meshes[i]);

        //this->total_vertices = model.indices;
        this->total_vertices.push_back(meshes[i].vertices);

        RenderableManager::addRenderable(this);
    }


	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Node::loadGLTFTexture(int i, Mesh const& mesh) {
    glBindTexture(GL_TEXTURE_2D, this->tos[i]);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

    //Setup a mipmap
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, mesh.sampler.minFilter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mesh.sampler.magFilter);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, mesh.image.width, mesh.image.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, mesh.image.image.data());
    glGenerateMipmap(GL_TEXTURE_2D);

    this->textured = true;

}

void Node::setScale(glm::vec3 const& scale) {
	this->scale_mat = glm::scale(glm::mat4(1.0f), glm::vec3(scale));
}
void Node::setPos(glm::vec3 const& pos) {
	this->pos_mat = glm::translate(glm::mat4(1.0f), glm::vec3(pos));
}

void Node::setOrientation(glm::vec3 const& orientation) {
    glm::quat x_rot = glm::angleAxis(glm::radians(orientation.x), glm::vec3(1.f, .0f, .0f));
    glm::quat y_rot = glm::angleAxis(glm::radians(orientation.y), glm::vec3(0.f, 1.f, .0f));
    glm::quat z_rot = glm::angleAxis(glm::radians(orientation.z), glm::vec3(0.f, .0f, 1.f));

    this->orientation = x_rot * y_rot * z_rot;
}


void Node::setScale(float x, float y, float z) {
	this->scale_mat = glm::scale(glm::mat4(1.0f), glm::vec3(x, y, z));
}
void Node::setPos(float x, float y, float z) {
	this->pos_mat = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, z));
}

void Node::calcModel() {
    this->model_mat = this->pos_mat * this->scale_mat * glm::toMat4(this->orientation);
}

void Node::setOrientation(float x, float y, float z) {
    glm::quat x_rot = glm::angleAxis(glm::radians(x), glm::vec3(1.f, .0f, .0f));
    glm::quat y_rot = glm::angleAxis(glm::radians(y), glm::vec3(0.f, 1.f, .0f));
    glm::quat z_rot = glm::angleAxis(glm::radians(z), glm::vec3(0.f, .0f, 1.f));

    this->orientation = x_rot * y_rot * z_rot;
}

void Node::glBind() const {
	glBindVertexArray(this->vao);
	glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
}


void Node::render() {

	assert(this->vbo != 0 && this->vao != 0 && this->ebo != 0);
	//this->shader.use();
    this->shader->use();
    this->glBind();
    //assert(this->view_proj != nullptr);
    glBindTexture(GL_TEXTURE_2D, 0);
    calcModel();
    if (is_wireframe) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        int MVPLoc = glGetUniformLocation(this->shader->id, "MVP");
        glm::mat4 MVP = this->view_proj * model_mat;
        glUniformMatrix4fv(MVPLoc, 1, GL_FALSE, glm::value_ptr(MVP));
        glDrawArrays(GL_TRIANGLES, 0, this->total_vertices[0]);
        return;
    }


    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    int model_loc = glGetUniformLocation(this->shader->id, "Model");
	glUniformMatrix4fv(model_loc, 1, GL_FALSE, glm::value_ptr(this->model_mat));

    glm::mat3 normal_mat = glm::transpose(glm::inverse(this->model_mat));
    int normal_mat_loc = glGetUniformLocation(this->shader->id, "normal_mat");
	glUniformMatrix3fv(normal_mat_loc, 1, GL_FALSE, glm::value_ptr(normal_mat));

	int MVPLoc = glGetUniformLocation(this->shader->id, "MVP");
	glm::mat4 MVP = this->view_proj * model_mat;
	int textured_loc = glGetUniformLocation(this->shader->id, "is_textured");
	glUniformMatrix4fv(MVPLoc, 1, GL_FALSE, glm::value_ptr(MVP));
    glUniform1i(textured_loc, this->textured);

    for (int i = 0; i < this->primitives_count; ++i) {
        if (this->tos != nullptr)
            glBindTexture(GL_TEXTURE_2D, this->tos[i]);

        glDrawArrays(GL_TRIANGLES, this->primitive_offsets[i], this->total_vertices[i]);
    }
}

Node::~Node() {
    delete[] tos;
    delete[] primitive_offsets;
}




