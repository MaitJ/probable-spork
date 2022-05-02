#ifndef WIREFRAME_H
#define WIREFRAME_H

#include "renderable_object.hpp"

class Wireframe {
    static Shader wf_shader;
    static RenderableObject wf_renderable;

    int entity_id;
    Transform& ent_transform;
    
public:
    Wireframe(Transform& transform, int entity_id);
    //Transformi sees on yhine render obj
    static void initWireframeModel();
    void render() const;
};



#endif
