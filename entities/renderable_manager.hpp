#ifndef RENDERABLE_MANAGER_H
#define RENDERABLE_MANAGER_H

#include "renderable_object.hpp"

namespace RenderableManager {

    void addRenderable(RenderableObject* obj);
    void renderObjects();
    void enableDimensionWireframes();
}

#endif
