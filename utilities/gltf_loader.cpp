#include "gltf_loader.hpp"
#include "glm/detail/type_quat.hpp"
#include "glm/gtx/quaternion.hpp"
#include <fmt/core.h>
#include "../entities/node.hpp"
#include <memory>
#include "mesh.hpp"

GLTFLoader::GLTFLoader(std::string const& file_name) {
    tinygltf::TinyGLTF loader;
    std::string warn;
    std::string err;

    loader.LoadASCIIFromFile(&this->model, &err, &warn, file_name);

    if (!warn.empty())
        fmt::print("[WARNING]: {0}\n", warn);

    if (!err.empty())
        fmt::print("[ERROR]: {0}\n", err);

}
template<typename ComponentType>
std::vector<ComponentType> GLTFLoader::getMeshIndices(tinygltf::Accessor const& indice_accessor) {
    using namespace tinygltf;

    std::vector<ComponentType> indices;
    indices.reserve(indice_accessor.count);
    BufferView& indice_bf_view = this->model.bufferViews[indice_accessor.bufferView];
    std::vector<unsigned char>& i_buffer_data = this->model.buffers[indice_bf_view.buffer].data;

    unsigned char* cur_byte = &i_buffer_data[indice_bf_view.byteOffset];

    for (int i = 0; i < indice_accessor.count; ++i) {
        ComponentType value = *reinterpret_cast<ComponentType*>(cur_byte);
        indices.insert(indices.begin() + i, value);

        cur_byte += sizeof(ComponentType) + indice_bf_view.byteStride;
    }

    return indices;
}

template <typename T>
void GLTFLoader::getAttribData(int accessor_index, int num_of_components, std::vector<T>& o_vec) {
    using namespace tinygltf;
    Accessor& accessor = this->model.accessors[accessor_index];
    BufferView& bf_view = this->model.bufferViews[accessor.bufferView];
    std::vector<unsigned char>& p_buffer_data = this->model.buffers[bf_view.buffer].data;

    unsigned char* cur_vertex_start = p_buffer_data.data() + bf_view.byteOffset + accessor.byteOffset;

    for (int i = 0; i < accessor.count; ++i) {
        unsigned char* cur_byte = cur_vertex_start;
        for (int j = 0; j < num_of_components; ++j) {
            T value = *reinterpret_cast<T*>(cur_byte);
            o_vec.push_back(value);

            cur_byte += sizeof(T);
        }
        if (bf_view.byteStride == 0) {
            cur_vertex_start += sizeof(T) * num_of_components;
        }
        else {
            cur_vertex_start += bf_view.byteStride;
        }
    }
}

//If the material isn't textured the object still gets colored
glm::quat GLTFLoader::nodeQuatToGLQuat(std::vector<double> quaternion) {
    return glm::inverse(glm::quat((float)quaternion[3], (float)quaternion[0], (float)quaternion[1], (float)quaternion[2]));
}

glm::vec3 GLTFLoader::nodeTransformToGLVec3F(std::vector<double> transform) {
    return {(float)transform[0], (float)transform[1], (float)transform[2]};
}

void GLTFLoader::groupVec3Floats(const std::vector<float> &floats, std::vector<glm::vec3>& o_vertices) {

    for (int i = 0; i < floats.size();) {
        glm::vec3 new_vector(.0f);
        new_vector.x = floats[i++];
        new_vector.y = floats[i++];
        new_vector.z = floats[i++];
        o_vertices.push_back(new_vector);
    }

}

void GLTFLoader::groupVec2Floats(const std::vector<float> &floats, std::vector<glm::vec2> &o_vertices) {

    int i = 0;
    while (i < floats.size()) {
        glm::vec2 new_vector(.0f);
        new_vector.x = floats[i++];
        new_vector.y = floats[i++];
        o_vertices.push_back(new_vector);
    }
}

void GLTFLoader::loadMesh(Renderable::Mesh& mesh) {

    for (int node_index : this->model.scenes[0].nodes) {
        Renderable::Node new_node;
        loadMeshRecursive(new_node, node_index);
        mesh.nodes.push_back(new_node);
    }
}

void GLTFLoader::loadMeshRecursive(Renderable::Node &node, int traverse_node_index) {
    tinygltf::Node& current_node = this->model.nodes[traverse_node_index];

    if (current_node.mesh != -1) {
        tinygltf::Mesh& mesh = this->model.meshes[current_node.mesh];

        for (tinygltf::Primitive& primitive : mesh.primitives) {
            tinygltf::Material& material = this->model.materials[primitive.material];

            std::shared_ptr<Renderable::Primitive> l_primitive;

            if (material.pbrMetallicRoughness.baseColorTexture.index != -1) {
                Shader const& textured_shader = ShaderManager::getShader("textured");
                auto renderable_primitive = std::make_shared<Renderable::TexturedPrimitive>(textured_shader);
                loadTexturedPrimitive(primitive, material, renderable_primitive);
                l_primitive = renderable_primitive;
            } else {
                Shader const& colored_shader = ShaderManager::getShader("colored");
                auto renderable_primitive = std::make_shared<Renderable::ColoredPrimitive>(colored_shader);
                loadColoredPrimitive(primitive, material, renderable_primitive);
                l_primitive = renderable_primitive;
            }

            node.primitives.emplace_back(l_primitive);

        }

        setNodeTransform(current_node, node);
    }

    if (!current_node.children.empty()) {
        for (int child_index : current_node.children) {
            Renderable::Node new_node;
            loadMeshRecursive(new_node, child_index);
            setNodeTransform(current_node, new_node);
            node.nodes.push_back(new_node);
        }
    }

}

void GLTFLoader::setNodeTransform(tinygltf::Node const& t_node, Renderable::Node& node) {
    glm::mat4 transform_matrix(1.f);
    glm::mat4 scale_mat(1.f);
    glm::mat4 rotation_mat(1.f);
    glm::mat4 translation_mat(1.f);

    if (!t_node.scale.empty()) {
        std::vector<double> const& scale = t_node.scale;
        scale_mat = glm::scale(transform_matrix, glm::vec3(
                scale[0],
                scale[1],
                scale[2]
        ));
    }

    if (!t_node.rotation.empty()) {
        //Quaternion
        rotation_mat = glm::toMat4(glm::quat(
                static_cast<float>(t_node.rotation[3]),
                static_cast<float>(t_node.rotation[0]),
                static_cast<float>(t_node.rotation[1]),
                static_cast<float>(t_node.rotation[2])
        ));

    }

    if (!t_node.translation.empty()) {
        std::vector<double> const& translation = t_node.translation;
        translation_mat = glm::translate(transform_matrix, glm::vec3(
                    translation[0], 
                    translation[1], 
                    translation[2]
                    ));
    }


    node.local_transform = translation_mat * rotation_mat * scale_mat;
}

void GLTFLoader::loadTexturedPrimitive(tinygltf::Primitive const& primitive,
                                       tinygltf::Material const& material,
                                       std::shared_ptr<Renderable::TexturedPrimitive> const& textured_primitive) {
    textured_primitive->genGlBuffers();
    textured_primitive->bindBuffers();

    std::vector<glm::vec3> position_vertices;
    std::vector<glm::vec3> normal_vertices;
    std::vector<glm::vec2> tex_vertices;
    std::vector<unsigned short> indices = this->getMeshIndices<unsigned short>(this->model.accessors[primitive.indices]);

    for (auto const& [key, value] : primitive.attributes) {
        if (key == "POSITION") {
            std::vector<float> pos;
            getAttribData<float>(value, 3, pos);
            groupVec3Floats(pos, position_vertices);
        }

        if (key == "NORMAL") {
            std::vector<float> normals;
            getAttribData<float>(value, 3, normals);
            groupVec3Floats(normals, normal_vertices);
        }

        if (key == "TEXCOORD_0") {
            std::vector<float> tex;
            getAttribData<float>(value, 2, tex);
            groupVec2Floats(tex, tex_vertices);
        }
    }


    textured_primitive->loadPrimitive(position_vertices, tex_vertices, normal_vertices, indices);

    const int texture_index = material.pbrMetallicRoughness.baseColorTexture.index;
    tinygltf::Texture& texture = this->model.textures[texture_index];
    tinygltf::Image& texture_image = this->model.images[texture.source];
    tinygltf::Sampler& sampler = this->model.samplers[texture.sampler];

    textured_primitive->loadMaterial(texture_image, sampler);
    textured_primitive->unbindBuffers();

}

void GLTFLoader::loadColoredPrimitive(tinygltf::Primitive const& primitive,
                                       tinygltf::Material const& material,
                                       std::shared_ptr<Renderable::ColoredPrimitive> const& colored_primitive) {
    colored_primitive->genGlBuffers();
    colored_primitive->bindBuffers();

    std::vector<glm::vec3> position_vertices;
    std::vector<glm::vec3> normal_vertices;
    std::vector<unsigned short> indices = this->getMeshIndices<unsigned short>(this->model.accessors[primitive.indices]);

    for (auto const& [key, value] : primitive.attributes) {
        if (key == "POSITION") {
            std::vector<float> pos;
            getAttribData<float>(value, 3, pos);
            groupVec3Floats(pos, position_vertices);
        }


        if (key == "NORMAL") {
            std::vector<float> normals;
            getAttribData<float>(value, 3, normals);
            groupVec3Floats(normals, normal_vertices);
        }
    }

    colored_primitive->loadPrimitive(position_vertices, normal_vertices, indices);
    colored_primitive->loadMaterial(material);
    colored_primitive->unbindBuffers();
}
