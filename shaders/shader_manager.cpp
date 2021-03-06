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
