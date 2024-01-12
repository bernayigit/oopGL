#pragma once

#include "buffers/buffer.hpp"

#include <GL/glew.h>
#include <unordered_map>

namespace ogl
{
    class VertexArray
    {
        public:
            VertexArray();

            void bind()   const;
            void unbind() const;
            
            size_t bindBuffer(const GLuint vbo, const size_t element_size, const size_t offset = 0);
            void   unbindBuffer(const size_t buffer_index);

            void enableAttributes (const VertexAttributes& attributes);
            void disableAttributes(const VertexAttributes& attributes);

            GLuint getId() const;

            ~VertexArray();

        protected: 
            GLuint id {};
            std::unordered_map<size_t, GLuint> buffers;

            size_t getAvailableIndex();
    };
}