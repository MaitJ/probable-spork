#ifndef SHADER_MANAGER_HPP
#define SHADER_MANAGER_HPP

#include "vector"
#include <glad/glad.h>
#include "../shader.hpp"

class ShaderManager {
public:
    static Shader const& getShader(std::string shader_name);
    static void addShader(Shader shader);

private:
    inline static std::vector<Shader> shaders = {};
};

#endif
