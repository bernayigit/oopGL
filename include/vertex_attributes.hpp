#pragma once

#include <span>
#include <vector>
#include <string>
#include <map>

#include "data.hpp"
#include "buffers/buffer.hpp"

#include "GL/glew.h"

namespace ogl
{
    class VertexAttributes
    {
        public:
            struct Attribute
            {
                size_t                 data_size;
                GLenum                 data_type;
                std::vector<std::byte> data;
            };

            VertexAttributes();

            template <typename T>
            VertexAttributes(
                const std::span<T> data, const GLenum data_type, const size_t index = 0
            );

            template <typename T>
            void setAttributes(
                const std::span<T> data, const GLenum data_type, const size_t index = 0
            );

            template <typename T>
            std::span<T> getAttributes(const size_t index = 0);

            void removeAttributes(const size_t index);

            bool hasChanged() const;
            void setChanged(const bool changed = true);

            const std::map<size_t, Attribute>& getAttributes() const;

            /*
            void enableAttribute(const GLuint VAO, const size_t index);
            void enableAllAttributes(const GLuint VAO);

            void disableAttribute(const GLuint VAO, const size_t index);
            */

            size_t getSize() const;

            std::span<std::byte> getData() const;

            size_t getStride() const;
            size_t getOffsetForAttribute(const size_t index) const;
            
    protected:
        bool alreadyContains(const size_t index);

        void computeData() const;

        mutable bool changed {true};

        std::map<size_t, Attribute> attributes;

        mutable std::vector<std::byte> data;
    };
}

#include "vertex_attributes.tpp"