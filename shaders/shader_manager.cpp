#include "shader_manager.hpp"
#include <fmt/core.h>

ShaderManager::ShaderManager() {}

Shader const& ShaderManager::getShader(std::string shader_name) const {
    for (Shader const& shader : this->shaders) {
        if (shader.name == shader_name)
            return shader;
    }

    fmt::print("[ERROR!] shader by name {0} wasn't found\n", shader_name);
    return *this->shaders.end();

}

void ShaderManager::addShader (Shader shader) {
    this->shaders.push_back(shader);
}
