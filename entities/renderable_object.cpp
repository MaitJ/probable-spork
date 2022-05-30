#include "renderable_object.hpp"
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

RenderableObject::RenderableObject(bool gen_buffers) : shader(MainShaders::getDefaultShader()), view_proj(RenderableManager::getViewProjMat()) {
    if (gen_buffers) {
        glGenVertexArrays(1, &this->vao);
        glGenBuffers(1, &this->vbo);
        glGenBuffers(1, &this->ebo);
    }
}
RenderableObject::RenderableObject(bool gen_buffers, Shader& shader) : shader(shader), view_proj(RenderableManager::getViewProjMat()) {
    if (gen_buffers) {
        glGenVertexArrays(1, &this->vao);
        glGenBuffers(1, &this->vbo);
        glGenBuffers(1, &this->ebo);
    }
    this->is_wireframe = true;
}

void RenderableObject::genBuffers() {
    glGenVertexArrays(1, &this->vao);
    glGenBuffers(1, &this->vbo);
    glGenBuffers(1, &this->ebo);
}

void RenderableObject::baseObjSetup(Utilities::Obj* obj) {

	glGenVertexArrays(1, &this->vao);
	glGenBuffers(1, &this->vbo);
	glGenBuffers(1, &this->ebo);
	glBindVertexArray(this->vao);

	glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
	glBufferData(GL_ARRAY_BUFFER, obj->triangles.size() * sizeof(float), obj->triangles.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, this->shader.layout_len * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

    this->tos = new unsigned int[1];
    glGenTextures(1, this->tos);
    glBindTexture(GL_TEXTURE_2D, this->tos[0]);
    this->texture_count = 1;

    this->primitives_count = 1;
    this->primitive_offsets = new unsigned int[1] { 0};

    //First have to bind texture object
    //If image isn't big enough
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

    //Setup a mipmap
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, this->shader.layout_len * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, this->shader.layout_len * sizeof(float), (void*)(5 * sizeof(float)));
    glEnableVertexAttribArray(2);
    

    this->total_vertices.push_back(obj->total_vertices);

    RenderableManager::addRenderable(this);
}

RenderableObject::RenderableObject(std::string obj_file) : shader(MainShaders::getDefaultShader()), view_proj(RenderableManager::getViewProjMat()) {
    Utilities::Obj* obj = new Utilities::Obj(obj_file);
    this->baseObjSetup(obj);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
    delete obj;
}

template <typename T>
unsigned int sumOfVerticesBytes(std::vector<Mesh> const& meshes) {
    unsigned int sum = 0;
    for (int i = 0; i < meshes.size(); ++i) {
        sum += meshes[i].vertex_data.size() * sizeof(T);
    }
    return sum;
}

void RenderableObject::loadGLTFModel(const std::string& file_name) {
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

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, this->shader.layout_len * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, this->shader.layout_len * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, this->shader.layout_len * sizeof(float), (void*)(5 * sizeof(float)));
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

void RenderableObject::loadGLTFTexture(int i, Mesh const& mesh) {
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
void RenderableObject::loadModel(std::string obj_file, std::string tex_file) {
    auto* obj = new Utilities::Obj(obj_file);

    //Throws error because this call doesn't include shader
    this->baseObjSetup(obj);
    this->loadTexture(tex_file);
    
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
    delete obj;
}

void RenderableObject::loadTexture(std::string tex_file) {
    int tex_width, tex_height, tex_nrchannels;
    unsigned char* img_data = stbi_load(tex_file.c_str(), &tex_width, &tex_height, &tex_nrchannels, 0);

    if (!img_data) {
        std::cerr << "Couldn't open image file" << std::endl;
        return;
    }
    this->textured = true;
    
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, tex_width, tex_height, 0, GL_RGB, GL_UNSIGNED_BYTE, img_data);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(img_data);
}

RenderableObject::RenderableObject(std::string obj_file, std::string tex_file) : shader(MainShaders::getDefaultShader()), view_proj(RenderableManager::getViewProjMat()) {
    Utilities::Obj* obj = new Utilities::Obj(obj_file);
    this->baseObjSetup(obj);

    this->loadTexture(tex_file);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
    delete obj;
}

void RenderableObject::setScale(glm::vec3 const& scale) {
	this->scale_mat = glm::scale(glm::mat4(1.0f), glm::vec3(scale));
}
void RenderableObject::setPos(glm::vec3 const& pos) {
	this->pos_mat = glm::translate(glm::mat4(1.0f), glm::vec3(pos));
}

void RenderableObject::setOrientation(glm::vec3 const& orientation) {
    glm::quat x_rot = glm::angleAxis(glm::radians(orientation.x), glm::vec3(1.f, .0f, .0f));
    glm::quat y_rot = glm::angleAxis(glm::radians(orientation.y), glm::vec3(0.f, 1.f, .0f));
    glm::quat z_rot = glm::angleAxis(glm::radians(orientation.z), glm::vec3(0.f, .0f, 1.f));

    this->orientation = x_rot * y_rot * z_rot;
}


void RenderableObject::setScale(float x, float y, float z) {
	this->scale_mat = glm::scale(glm::mat4(1.0f), glm::vec3(x, y, z));
}
void RenderableObject::setPos(float x, float y, float z) {
	this->pos_mat = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, z));
}

void RenderableObject::calcModel() {
    this->model_mat = this->pos_mat * this->scale_mat * glm::toMat4(this->orientation);
}

void RenderableObject::setOrientation(float x, float y, float z) {
    glm::quat x_rot = glm::angleAxis(glm::radians(x), glm::vec3(1.f, .0f, .0f));
    glm::quat y_rot = glm::angleAxis(glm::radians(y), glm::vec3(0.f, 1.f, .0f));
    glm::quat z_rot = glm::angleAxis(glm::radians(z), glm::vec3(0.f, .0f, 1.f));

    this->orientation = x_rot * y_rot * z_rot;
}

void RenderableObject::glBind() const {
	glBindVertexArray(this->vao);
	glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
}


void RenderableObject::render() {

	assert(this->vbo != 0 && this->vao != 0 && this->ebo != 0);
	this->shader.use();
    this->glBind();
    //assert(this->view_proj != nullptr);
    calcModel();
    if (is_wireframe) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        int MVPLoc = glGetUniformLocation(this->shader.id, "MVP");
        glm::mat4 MVP = this->view_proj * model_mat;
        glUniformMatrix4fv(MVPLoc, 1, GL_FALSE, glm::value_ptr(MVP));
        glDrawArrays(GL_TRIANGLES, 0, this->total_vertices[0]);
        return;
    }


    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    int model_loc = glGetUniformLocation(this->shader.id, "Model");
	glUniformMatrix4fv(model_loc, 1, GL_FALSE, glm::value_ptr(this->model_mat));

    glm::mat3 normal_mat = glm::transpose(glm::inverse(this->model_mat));
    int normal_mat_loc = glGetUniformLocation(this->shader.id, "normal_mat");
	glUniformMatrix3fv(normal_mat_loc, 1, GL_FALSE, glm::value_ptr(normal_mat));

	int MVPLoc = glGetUniformLocation(this->shader.id, "MVP");
	glm::mat4 MVP = this->view_proj * model_mat;
	int textured_loc = glGetUniformLocation(this->shader.id, "is_textured");
	glUniformMatrix4fv(MVPLoc, 1, GL_FALSE, glm::value_ptr(MVP));
    glUniform1i(textured_loc, this->textured);

    for (int i = 0; i < this->primitives_count; ++i) {
        if (this->tos != nullptr)
            glBindTexture(GL_TEXTURE_2D, this->tos[i]);

        glDrawArrays(GL_TRIANGLES, this->primitive_offsets[i], this->total_vertices[i]);
    }
}

RenderableObject::~RenderableObject() {
    delete[] tos;
    delete[] primitive_offsets;
}


