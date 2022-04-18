set(TESTS_SOURCE catch_init.cpp glm_matchers.cpp obj_loader_test.cpp
    event_handler_test.cpp)
set(TESTS_PROJ_NAME "${PROJECT_NAME}_tests")

add_executable(${TESTS_PROJ_NAME} ${TESTS_SOURCE})
find_package(Catch2 REQUIRED)
target_link_libraries(${TESTS_PROJ_NAME} source)
target_link_libraries(${TESTS_PROJ_NAME} Catch2::Catch2)

configure_file("${CMAKE_CURRENT_SOURCE_DIR}/test_obj.obj"
    "${CMAKE_CURRENT_BINARY_DIR}/test_obj.obj")

