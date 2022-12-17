#ifndef WIREFRAME_H
#define WIREFRAME_H

#include "renderables/mesh/node.hpp"
#include "shaders/shader_manager.hpp"

namespace Renderable {
    class Mesh;
}

class Wireframe {
    static Renderable::Node wf_renderable;

    int entity_id;
    Transform& ent_transform;
    
public:
    Wireframe(Transform& transform, int entity_id);

    //Transformi sees on yhine render obj
    static void initWireframeModel();
    void render(Context& ctx, glm::mat4 const& VP) const;
};



#endif
