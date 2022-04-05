#include <catch2/catch.hpp>
#include "../shader.hpp"
#include "../utilities/obj.hpp"

TEST_CASE("Obj file gets correctly read", "[obj_model]") {
    Utilities::Obj test_file("tests/test_obj.obj");

    float* test_file_vertices = new float[test_file.vertices.size() * 3];

    for (int i = 0; i < test_file.vertices.size(); ++i) {
        test_file_vertices[(3 * i)] = test_file.vertices[i].x;
        test_file_vertices[(3 * i) + 1] = test_file.vertices[i].y;
        test_file_vertices[(3 * i) + 2] = test_file.vertices[i].z;
    }

    float file_vertices[] = {
        1.0f, 1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, -1.0f, 1.0f
    };

    float file_normals[] = {
        -0.0f, 1.0f, -0.0f,
        -0.0f, -0.0f, 1.0f,
        -1.0f, -0.0f, -0.0f,
        -0.0f, -0.0f, -1.0f
    };

    float file_textures[] = {
        0.250050f, 0.250050f,
        0.250250f, 0.500200f,
        0.70000f, 1.00000f,
        1.00000f, 1.00000f
    };

    SECTION("Vertices get read correctly") {
       REQUIRE(file_vertices == test_file_vertices);
    }

}
