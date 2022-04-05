cmake_minimum_required(VERSION 3.20)
project(PoeLite)
set(CMAKE_CXX_STANDARD 23)
set(DEPS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/deps")
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_EXPORT_COMPILE_COMMANDS true)

set(SOURCE_FILES main.cpp shader.cpp window.cpp utilities/obj.cpp "entities/renderable_object.cpp")

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_include_directories(${PROJECT_NAME} PRIVATE utilities)
target_include_directories(${PROJECT_NAME} PRIVATE entities)

add_subdirectory("${DEPS_DIR}/glfw")
target_link_libraries(${PROJECT_NAME} glfw)
find_package(OpenGL REQUIRED)
target_link_libraries(${PROJECT_NAME} OpenGL::GL)

add_library(glad STATIC "${DEPS_DIR}/glad/glad.c")
target_include_directories(glad PUBLIC "${DEPS_DIR}/")
target_link_libraries(${PROJECT_NAME} glad)

add_subdirectory("${DEPS_DIR}/glm")
target_link_libraries(${PROJECT_NAME} glm)
