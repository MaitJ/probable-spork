#include "shader_manager.hpp"
#include <fmt/core.h>

Shader const& ShaderManager::getShader(std::string shader_name) {
    for (Shader const& shader : shaders) {
        if (shader.name == shader_name)
            return shader;
    }

    fmt::print("[ERROR!] shader by name {0} wasn't found\n", shader_name);
    return *shaders.end();

}

void ShaderManager::addShader (Shader shader) {
    shaders.push_back(shader);
}

void ShaderManager::initializeShaders() {
    std::vector<std::string> shader_names = {"textured", "wireframe", "colored"};
    std::vector<std::string> vertex_shader_files = {"vertex_shader_textured.vert", "wf_vertex_shader.vert", "vertex_shader_colored.vert"};
    std::vector<std::string> fragment_shader_files = {"fragment_shader_textured.frag", "wf_fragment_shader.frag", "fragment_shader_colored.frag"};

    for (int i = 0; i < shader_names.size(); ++i) {
        Shader shader;
        shader.loadAndCompile(vertex_shader_files[i], fragment_shader_files[i], shader_names[i]);

        ShaderManager::addShader(shader);
    }
}
