#include "renderable_manager.hpp"



namespace RenderableManager {
    namespace {
        bool wireframes_enabled = false;
        std::vector<RenderableObject*> renderables;
    }

    void addRenderable(RenderableObject* obj) {
        renderables.push_back(obj);
    }

    void renderObjects() {
        if (!wireframes_enabled) {
            for (RenderableObject* obj : renderables) {
                obj->render();
            }
        }
    }

    void enableDimensionWireframes() {
        //Not implemented yet.
        return;
    }
}

