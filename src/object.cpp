#include "object.hpp"

namespace ogl
{
    void Object::loadOnBuffer()
    {

    }

    VertexArray& Object::getVertexArray()
    {
        return *VAO;
    }

    Object::Buffer& Object::getVertexBuffer()
    {
        return *VBO;
    }

    const VertexArray& Object::getVertexArray() const
    {
        return *VAO;
    }

    const Object::Buffer& Object::getVertexBuffer() const
    {
        return *VBO;
    }

    void ogl::Object::setVertexBuffer(std::shared_ptr<Buffer> vertex_buffer)
    {
        VBO = vertex_buffer;
    }

    void ogl::Object::setVertexArray(std::shared_ptr<VertexArray> vertex_array)
    {
        VAO = vertex_array;
    }    

    // Static VAO and VBO

    std::shared_ptr<VertexArray>    Object::VAO {nullptr};
    std::shared_ptr<Object::Buffer> Object::VBO {nullptr};
}