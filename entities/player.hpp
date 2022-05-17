#ifndef PLAYER_H
#define PLAYER_H

#include <glm/glm.hpp>
#include "renderable_object.hpp"
#include "../components/transform.hpp"
#include "entity.hpp"
#include "camera.hpp"
#include "../utilities/deltatime.hpp"
#include <memory>

class Context;

enum CollisionAxis {
    X = 0,
    Y = 1,
    Z = 2
};

struct Player {

    Player(Camera& camera, Context& ctx);
    Player(glm::mat4& view_proj, Shader* shader, Camera& camera, Context& ctx);
    bool isVisible();

    void updateMovement(DeltaTime const& dt);
    
    std::shared_ptr<Entity> game_ent;
    Camera& camera;

    void resetCameraPos();

private:
    bool is_visible = false;

    RenderableObject render_obj;
    void setupRenderable(glm::mat4& view_proj, Shader* shader);

    void getMovementInputs();
    void handleCollisions();
    void performMovement(float& player_axis, float& camera_axis, float const& camera_front_axis);

    void limitMovement();
    void resolveCollision(CollisionAxis collision_axis);



    glm::vec3 velocity = glm::vec3(0.f);
    glm::vec3 acceleration = glm::vec3(0.f);

    void setVelocity(float const x, float const y, float const z);
    void setVelocity(glm::vec3 const velocity);

    glm::vec3& getVelocity();

    float head_offset = 20.f;

    float friction = .8f;
    float speed = 25.f;


};
#endif
