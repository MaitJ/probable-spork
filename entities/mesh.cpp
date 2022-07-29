#include "mesh.hpp"
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "renderable_manager.hpp"

namespace Renderable {
    void Primitive::unbindBuffers() {
        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    ColoredPrimitive::ColoredPrimitive(const Shader &shader) : shader(shader) {}

    void ColoredPrimitive::genGlBuffers() {
        glGenVertexArrays(1, &this->vao);
        glGenBuffers(1, &this->vbo);
    }

    void ColoredPrimitive::bindBuffers() {
        glBindVertexArray(this->vao);
        glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
    }


    auto ColoredPrimitive::assembleVertices(std::vector<glm::vec3> const& positions,
                                                        std::vector<unsigned short> const& indices,
                                                        std::vector<glm::vec3> const& normals) -> std::vector<float> {
        std::vector<float> vertex_data;

        for (unsigned short mesh_index : indices) {
            vertex_data.insert(vertex_data.end(), {positions[mesh_index][0], positions[mesh_index][1], positions[mesh_index][2]});
            vertex_data.insert(vertex_data.end(), {normals[mesh_index][0], normals[mesh_index][1], normals[mesh_index][2]});
        };

        return vertex_data;

    }

    void ColoredPrimitive::loadPrimitive(std::vector<glm::vec3> const& positions,
                                                     std::vector<glm::vec3> const& normals,
                                                     std::vector<unsigned short> const& indices) {

        std::vector<float> vertex_data = this->assembleVertices(positions, indices, normals);
        this->vertices = indices.size();

        glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_data) * vertices, vertex_data.data(), GL_STATIC_DRAW); // NOLINT

        const GLint vertex_length = 6;
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, vertex_length * sizeof(float), (void*)0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, vertex_length * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);

    }

    void ColoredPrimitive::loadMaterial(tinygltf::Material const& material) {
        std::vector<double> color = material.pbrMetallicRoughness.baseColorFactor;
        this->color = glm::vec4(color[0], color[1], color[2], color[3]);
    }

    void ColoredPrimitive::render(glm::mat4& global_transform, glm::mat4& model_matrix, Context const& ctx) {
        this->shader.use();
        this->bindBuffers();

        int light_pos_loc = glGetUniformLocation(this->shader.id, "light_pos");
        glUniform3fv(light_pos_loc, 1, glm::value_ptr(ctx.world_light.position));

        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        int model_loc = glGetUniformLocation(this->shader.id, "Model");
        glUniformMatrix4fv(model_loc, 1, GL_FALSE, glm::value_ptr(model_matrix));

        glm::mat3 normal_mat = glm::transpose(glm::inverse(model_matrix));
        int normal_mat_loc = glGetUniformLocation(this->shader.id, "normal_mat");
        glUniformMatrix3fv(normal_mat_loc, 1, GL_FALSE, glm::value_ptr(normal_mat));

        int MVPLoc = glGetUniformLocation(this->shader.id, "MVP");
        glm::mat4 MVP = global_transform * model_matrix;
        glUniformMatrix4fv(MVPLoc, 1, GL_FALSE, glm::value_ptr(MVP));

        int color_loc = glGetUniformLocation(this->shader.id, "vertex_color");
        glUniform3fv(color_loc, 1, glm::value_ptr(this->color));

        glDrawArrays(GL_TRIANGLES, 0, this->vertices); // NOLINT

    }

    void ColoredPrimitive::loadPrimitive(std::vector<float> const& vertex_data, int vertices) {
        this->vertices = vertices;

        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertex_data.size(), vertex_data.data(), GL_STATIC_DRAW); // NOLINT

        const GLint vertex_length = 6;
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, vertex_length * sizeof(float), (void*)0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, vertex_length * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
    }
    void ColoredPrimitive::loadColor(glm::vec4 color) {
        this->color = color;
    }

    TexturedPrimitive::TexturedPrimitive(const Shader &shader) : shader(shader) {}

    void Renderable::TexturedPrimitive::bindBuffers() {
        glBindVertexArray(this->vao);
        glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
        glBindTexture(GL_TEXTURE_2D, this->to);
    }

    void Renderable::TexturedPrimitive::genGlBuffers() {
        glGenVertexArrays(1, &this->vao);
        glGenBuffers(1, &this->vbo);
        glGenBuffers(1, &this->to);
    }


    auto TexturedPrimitive::assembleVertices(std::vector<glm::vec3> const& positions,
                                                                       std::vector<glm::vec2> const& tex_coords,
                                                                       std::vector<glm::vec3> const& normals,
                                                                       std::vector<unsigned short> const& indices) -> std::vector<float> {
        std::vector<float> vertex_data;

        for (unsigned short mesh_index : indices) {
            vertex_data.insert(vertex_data.end(), {positions[mesh_index][0], positions[mesh_index][1], positions[mesh_index][2]});
            vertex_data.insert(vertex_data.end(), {normals[mesh_index][0], normals[mesh_index][1], normals[mesh_index][2]});
            vertex_data.insert(vertex_data.end(), {tex_coords[mesh_index][0], tex_coords[mesh_index][1]});
        };

        return vertex_data;

    }

    void TexturedPrimitive::loadPrimitive(std::vector<glm::vec3> const& positions,
                                                      std::vector<glm::vec2> const& tex_coords,
                                                      std::vector<glm::vec3> const& normals,
                                                      std::vector<unsigned short> const& indices) {

        std::vector<float> vertex_data = this->assembleVertices(positions, tex_coords, normals, indices);
        this->vertices = indices.size();

        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertex_data.size(), vertex_data.data(), GL_STATIC_DRAW); // NOLINT

        const GLint vertex_length = 8;
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, vertex_length * sizeof(float), (void*)0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, vertex_length * sizeof(float), (void*)(3 * sizeof(float)));
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, vertex_length * sizeof(float), (void*)(6 * sizeof(float)));
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glEnableVertexAttribArray(2);

    }

    void TexturedPrimitive::loadMaterial(tinygltf::Image const& image, tinygltf::Sampler const& sampler) {
        glBindTexture(GL_TEXTURE_2D, this->to);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

        if (sampler.wrapS != -1) {
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, sampler.wrapS);
        }
        if (sampler.wrapT != -1) {
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, sampler.wrapT);
        }

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        if (sampler.minFilter != -1) {
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, sampler.minFilter);
        }
        if (sampler.magFilter != -1) {
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, sampler.magFilter);
        }
        //Setup a mipmap

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.width, image.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.image.data());
        glGenerateMipmap(GL_TEXTURE_2D);

    }
    void TexturedPrimitive::render(glm::mat4& global_transform, glm::mat4& model_matrix, Context const& ctx) {
        this->shader.use();
        this->bindBuffers();

        int light_pos_loc = glGetUniformLocation(this->shader.id, "light_pos");
        glUniform3fv(light_pos_loc, 1, glm::value_ptr(ctx.world_light.position));

        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        int model_loc = glGetUniformLocation(this->shader.id, "Model");
        glUniformMatrix4fv(model_loc, 1, GL_FALSE, glm::value_ptr(model_matrix));

        glm::mat3 normal_mat = glm::transpose(glm::inverse(model_matrix));
        int normal_mat_loc = glGetUniformLocation(this->shader.id, "normal_mat");
        glUniformMatrix3fv(normal_mat_loc, 1, GL_FALSE, glm::value_ptr(normal_mat));

        int MVPLoc = glGetUniformLocation(this->shader.id, "MVP");
        glm::mat4 MVP = global_transform * model_matrix;
        glUniformMatrix4fv(MVPLoc, 1, GL_FALSE, glm::value_ptr(MVP));

        glBindTexture(GL_TEXTURE_2D, this->to);

        glDrawArrays(GL_TRIANGLES, 0, this->vertices); // NOLINT
    }

    void Mesh::render(const Context &ctx, glm::mat4 const& VP) {
        //View projection matrix and camera matrix are missing
        glm::mat4 model_matrix = this->transform.getTransformationMatrix();

        for (auto& node : this->nodes){
            node.render(ctx, VP, model_matrix);
        }
    }

    void Mesh::loadGLTFModel(std::string const& file_name) {
        GLTFLoader model(file_name);
        model.loadMesh(*this);
        RenderableManager::addRenderableMesh(this);
    }
}

