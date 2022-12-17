#include "primitive.hpp"

namespace Renderable {
    void Primitive::unbindBuffers() {
        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}
