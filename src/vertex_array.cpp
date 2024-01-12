#include "vertex_array.hpp"
#include "vertex_attributes.hpp"

#include <random>

namespace ogl
{
    VertexArray::VertexArray()
    {
        glCreateVertexArrays(1, &id);
    }

    void VertexArray::bind() const
    {
        glBindVertexArray(id);
    }

    void VertexArray::unbind() const
    {
        glBindVertexArray(0);
    }

    size_t VertexArray::bindBuffer(
        const GLuint vbo,
        const size_t elem_size,
        const size_t offs
    )
    {
        const auto index {getAvailableIndex()};

        buffers[index] = vbo;

        glVertexArrayVertexBuffer(
            id,
            index,
            vbo,
            offs,
            elem_size
        );

        return index;
    }

    void VertexArray::unbindBuffer(const size_t buffer_index)
    {
        buffers.erase(buffer_index);

        // Impossible to know how to unbind buffer
    }
 
    void VertexArray::enableAttributes(const VertexAttributes& attributes)
    {
        for(const auto&[index, attribute] : attributes.getAttributes())
        {
            for(const auto&[binding_index, buffer] : buffers)
            {
                glVertexArrayAttribBinding(
                    id,
                    index,
                    binding_index
                );

                glVertexArrayAttribFormat(
                    id,
                    index,
                    attribute.data_size,
                    attribute.data_type,
                    GL_FALSE,
                    attributes.getOffsetForAttribute(index)
                );
            }
        }
    }

    void VertexArray::disableAttributes(const VertexAttributes& attributes)
    {
        for(const auto&[index, attribute] : attributes.getAttributes())
        {
            glDisableVertexArrayAttrib(id, index);
        }
    }

    GLuint VertexArray::getId() const
    {
        return id;
    }

    VertexArray::~VertexArray()
    {
        glDeleteVertexArrays(1, &id);
    }

    size_t VertexArray::getAvailableIndex()
    {
        static std::mt19937 random_gen {};
        static std::uniform_int_distribution<size_t> dist {0, buffers.max_size()};

        size_t key {dist(random_gen)};
        
        for(; buffers.contains(key); key = dist(random_gen))
        {
        }

        return key;
    }
}