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

struct Player {

    Player(Camera& camera, Context& ctx);
    Player(glm::mat4& view_proj, Shader* shader, Camera& camera, Context& ctx);
    bool isVisible();
    void onMove(Direction dir);

    void updateMovement(DeltaTime const& dt);
    
    std::shared_ptr<Entity> game_ent;
    Camera& camera;

private:
    bool is_visible = false;

    RenderableObject render_obj;
    void setupRenderable(glm::mat4& view_proj, Shader* shader);

    void handleCollisions(glm::vec3 const& camera_front, bool in_positive_dir);
    void performMovement(float& player_axis, float& camera_axis, float const& camera_front_axis, bool in_positive_dir);



    glm::vec3 velocity = glm::vec3(0.f);

    void setVelocity(float const x, float const y, float const z);
    void setVelocity(glm::vec3 const velocity);

    glm::vec3& getVelocity();


    float friction = .2f;
    float speed = 2.f;


};
#endif
