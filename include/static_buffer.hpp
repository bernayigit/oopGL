#pragma once

#include "buffer.hpp"

namespace ogl
{
    template <typename Key = const VertexAttributes*>
    class StaticBuffer : public Buffer<Key>
    {
        public:
            StaticBuffer(const size_t size, GLbitfield flags);
            
            void upload() override;

            bool set   (const VertexAttributes& data) override;
            bool remove(const Key& key)               override;

            ~StaticBuffer();

        protected:
            const size_t size {};
    };
}

#include "static_buffer.tpp"