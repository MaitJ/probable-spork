#include "gltf_loader.hpp"
#include "glm/detail/type_quat.hpp"
#include "glm/gtx/quaternion.hpp"
#include <fmt/core.h>

GLTFLoader::GLTFLoader(std::string const& file_name, bool& loaded) : indices{0} {
    tinygltf::TinyGLTF loader;
    std::string warn;
    std::string err;

    loaded = loader.LoadASCIIFromFile(&this->model, &err, &warn, file_name);

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

    unsigned char* cur_byte = &p_buffer_data[bf_view.byteOffset];

    for (int i = 0; i < (accessor.count * num_of_components); ++i) {
        T value = *reinterpret_cast<T*>(cur_byte);
        o_vec.insert(o_vec.begin() + i, value);

        cur_byte += sizeof(T) + bf_view.byteStride;
    }
}

//If the material isn't textured the object still gets colored
void GLTFLoader::setImageMaterial(Mesh& t_mesh, int material_index) {
    tinygltf::Material& primitive_material = this->model.materials[material_index];

    std::vector<double> const& color = primitive_material.pbrMetallicRoughness.baseColorFactor;
    glm::vec4 node_color = {color[0], color[1], color[2], color[3]};
    t_mesh.color = node_color;

    tinygltf::Texture& texture = this->model.textures[primitive_material.
            pbrMetallicRoughness.
            baseColorTexture.index];
    tinygltf::Sampler& sampler = this->model.samplers[texture.sampler];
    tinygltf::Image& image = this->model.images[texture.source];

    t_mesh.sampler = sampler;
    t_mesh.material = primitive_material;
    t_mesh.image = image;

    if (primitive_material.pbrMetallicRoughness.baseColorTexture.index > -1)
        t_mesh.is_textured = true;

}

void GLTFLoader::getMeshData(tinygltf::Node const& node, Mesh& t_mesh) {
    using namespace tinygltf;
    std::vector<tinygltf::Accessor>& accessors = this->model.accessors;

    std::vector<float> vertex_data;

    tinygltf::Mesh& mesh = this->model.meshes[node.mesh];

    for (tinygltf::Primitive& primitive : mesh.primitives) {

        std::vector<glm::vec3> position_vertices;
        std::vector<glm::vec3> normal_vertices;
        std::vector<glm::vec2> tex_vertices;

        setImageMaterial(t_mesh, primitive.material);


        for (auto& [key, value] : primitive.attributes) {

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

        //Apply node transformations
        applyNodeTransformations(node, position_vertices, normal_vertices);

        Accessor& indice_accessor = accessors[primitive.indices];

        switch (indice_accessor.componentType) {
            case TINYGLTF_COMPONENT_TYPE_UNSIGNED_SHORT:
                std::vector<unsigned short> mesh_indices = getMeshIndices<unsigned short>(indice_accessor);

                t_mesh.vertices = mesh_indices.size();

                for (unsigned short mesh_index : mesh_indices) {
                    vertex_data.insert(vertex_data.end(), {position_vertices[mesh_index][0], position_vertices[mesh_index][1], position_vertices[mesh_index][2]});
                    vertex_data.insert(vertex_data.end(), {tex_vertices[mesh_index][0], tex_vertices[mesh_index][1]});
                    vertex_data.insert(vertex_data.end(), {normal_vertices[mesh_index][0], normal_vertices[mesh_index][1], normal_vertices[mesh_index][2]});

                    //vertex_data.insert(vertex_data.end(), {t_mesh.color[0], t_mesh.color[1], t_mesh.color[2], t_mesh.color[3]});
                }


            break;

        }

    }
        

    t_mesh.vertex_data = vertex_data;
}

void GLTFLoader::applyNodeTransformations(tinygltf::Node const& node, std::vector<glm::vec3>& position_vertices, std::vector<glm::vec3>& normal_vertices) {
    glm::vec3 t_translation(0.f);
    glm::quat t_rotation;
    glm::vec3 t_scale(1.f);

    if (!node.scale.empty())
        t_scale = nodeTransformToGLVec3F(node.scale);

    if (!node.rotation.empty())
        t_rotation = nodeQuatToGLQuat(node.rotation);

    nodeTransformMesh(t_translation, t_rotation, t_scale, position_vertices, normal_vertices);
}

glm::quat GLTFLoader::nodeQuatToGLQuat(std::vector<double> quaternion) {
    return glm::inverse(glm::quat((float)quaternion[3], (float)quaternion[0], (float)quaternion[1], (float)quaternion[2]));
}

glm::vec3 GLTFLoader::nodeTransformToGLVec3F(std::vector<double> transform) {
    return {(float)transform[0], (float)transform[1], (float)transform[2]};
}

//Because I can't insert vec4's into vertex_data beacuse of shader
//here the translation property is useless
void GLTFLoader::nodeTransformMesh(glm::vec3 translation,
                               glm::quat rotation,
                               glm::vec3 scale,
                               std::vector<glm::vec3>& position_vertices,
                               std::vector<glm::vec3>& normal_vertices) {

    glm::mat4 scale_mat = glm::scale(glm::mat4(1.f), scale);
    glm::mat4 translation_mat = glm::translate(glm::mat4(1.f), translation);
    glm::mat4 rotation_mat = glm::toMat4(rotation);

    glm::mat4 MVP = translation_mat * rotation_mat * scale_mat;

    for (auto& pos : position_vertices) {
        glm::vec4 result = glm::vec4(pos, 1.f) * MVP;
        pos = result;
    }

    for (auto& normal : normal_vertices) {
        glm::vec4 result = glm::vec4(normal, 1.f) * MVP;
        normal = result;

    }


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

std::vector<Mesh> GLTFLoader::getMeshes() {

    std::vector<Mesh> meshes;

    for (auto& node : this->model.nodes) {
        Mesh t_mesh;

        getMeshData(node, t_mesh);

        meshes.push_back(t_mesh);
    }

    return meshes;
}
