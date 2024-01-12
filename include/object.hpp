#pragma once

#include <memory>

#include "..\vertex_attributes.hpp"
#include "..\buffers/buffer.hpp"
#include "..\vertex_array.hpp"

namespace ogl
{
    class Object
    {
        public:
            using Buffer = Buffer<const VertexAttributes*, std::vector<std::byte>>;

            virtual void draw() const = 0;

            void loadOnBuffer();

            void setVertexBuffer(std::shared_ptr<Buffer>      vertex_buffer);
            void setVertexArray (std::shared_ptr<VertexArray> vertex_array);

            VertexArray& getVertexArray ();
            Buffer&      getVertexBuffer();

            const VertexArray& getVertexArray () const;
            const Buffer&      getVertexBuffer() const;

        protected:
            VertexAttributes attributes;

            static std::shared_ptr<VertexArray> VAO;
            static std::shared_ptr<Buffer>      VBO; 

            //static void enableAttributes();

            size_t buffer_id {};
    };
}