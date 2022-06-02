#ifndef SHADER_MANAGER_HPP
#define SHADER_MANAGER_HPP

#include "vector"
#include <glad/glad.h>
#include "../shader.hpp"

class ShaderManager {
public:
    ShaderManager();

    Shader const& getShader(std::string shader_name) const;
    void addShader(Shader shader);

private:
    std::vector<Shader> shaders;
};

#endif
