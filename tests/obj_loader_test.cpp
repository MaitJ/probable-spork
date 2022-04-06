#include <catch2/catch.hpp>
#include "../shader.hpp"
#include "../utilities/obj.hpp"
#include <unistd.h>
#include <iostream>
#include <sstream>
#include <iterator>
#include "glm_matchers.cpp"


TEST_CASE("Obj file gets correctly read", "[obj_model]") {
    Utilities::Obj test_file("tests/test_obj.obj");

    std::vector<glm::vec3> correct_vertices_vec = {
        glm::vec3(1.0f, 1.0f, -1.0f),
        glm::vec3(1.0f, -1.0f, -1.0f),
        glm::vec3(1.0f, 1.0f, 1.0f),
        glm::vec3(1.0f, -1.0f, 1.0f)
    };


    std::vector<glm::vec3> file_normals = {
        glm::vec3(-0.0f, 1.0f, -0.0f),
        glm::vec3(-0.0f, -0.0f, 1.0f),
        glm::vec3(-1.0f, -0.0f, -0.0f),
        glm::vec3(-0.0f, -0.0f, -1.0f)
    };

    std::vector<glm::vec2> file_textures = {
        glm::vec2(0.250050f, 0.250050f),
        glm::vec2(0.250250f, 0.500200f),
        glm::vec2(0.70000f, 1.00000f),
        glm::vec2(1.00000f, 1.00000f)
    };

    SECTION("Vertices get read correctly") {
        REQUIRE_THAT(correct_vertices_vec, IsGlmVecsEqual<std::vector<glm::vec3>>(test_file.vertices));
    }
    SECTION("Texture coordinates get read correctly") {
        REQUIRE_THAT(file_textures, IsGlmVecsEqual<std::vector<glm::vec2>>(test_file.tex_vertices));
    }
    SECTION("Normals get read correctly") {
        REQUIRE_THAT(file_normals, IsGlmVecsEqual<std::vector<glm::vec3>>(test_file.vec_normals));
    }

}
