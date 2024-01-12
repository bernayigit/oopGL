#pragma once

#include <cstring>

namespace ogl
{
    inline VertexAttributes::VertexAttributes()
    :
        attributes{}, data{}
    {
    }

    template <typename T>
    inline VertexAttributes::VertexAttributes(
        const std::span<T> data, const GLenum data_type, const size_t index
    )
    :
        attributes{}, data{}
    {
        setAttributes(index, data, data_type);
    }

    template <typename T>
    inline void VertexAttributes::setAttributes(
        const std::span<T> data, const GLenum data_type, const size_t index
    )
    {
        changed = true;

        attributes[index].data      = data;
        attributes[index].data_type = data_type;
        attributes[index].data_size = sizeof(T);
    }

    template <typename T>
    inline std::span<T> VertexAttributes::getAttributes(const size_t index)
    {
        return attributes[index].data;
    }

    inline void VertexAttributes::removeAttributes(const size_t index)
    {
        if(attributes.contains(index))
        {
            attributes.erase(index);
        }
    }

    inline bool VertexAttributes::hasChanged() const 
    {
        return changed;
    }

    inline size_t VertexAttributes::getSize() const
    {
        return attributes.begin()->second.data.size() * attributes.size();
    }

    inline std::span<std::byte> VertexAttributes::getData() const
    {
        if(changed)
        {
            computeData();

            changed = false;
        }

        return data;
    }

    inline size_t VertexAttributes::getStride() const
    {
        size_t stride {};

        for(const auto&[key, attribute] : attributes)
        {
            stride += attribute.data_size;
        }

        return stride;
    }

    inline bool VertexAttributes::alreadyContains(const size_t index)
    {
        return attributes.contains(index);
    }

    inline size_t VertexAttributes::getOffsetForAttribute(const size_t index) const
    {
        size_t offset {};

        for(const auto&[key, attribute] : attributes)
        {
            if(!(key < index))
            {
                break;
            } 

            offset += attribute.data_size;
        }

        return offset;
    }

    inline void VertexAttributes::computeData() const
    {
        data.resize(getSize());

        if(!attributes.empty())
        {
            for(size_t i {}; i < attributes.begin()->second.data.size(); ++i)
            {
                for(const auto&[key, attribute] : attributes)
                {
                    memcpy(
                        data.data() + getOffsetForAttribute(key) + getStride() * i,
                        &attribute.data[i],
                        attribute.data_size
                    );
                }
            }
        }
    }

    inline const std::map<size_t, VertexAttributes::Attribute>& VertexAttributes::getAttributes() const
    {
        return attributes;
    }

    inline void VertexAttributes::setChanged(const bool t_changed)
    {
        changed = t_changed;
    }

/*
   void VertexAttributes::enableAllAttributes(const GLuint VAO)
    {
        for(const auto&[key, attribute] : attributes)
        {
            enableAttribute(VAO, key);
        }
    }

    void VertexAttributes::enableAttribute(const GLuint VAO, const size_t index)
    {
        glEnableVertexArrayAttrib(VAO, index);
        glVertexArrayAttribFormat(
            VAO,
            index,
            1,
            attributes[index].data_type,
            GL_FALSE,
            getStride()
        );
    }

    void disableAttribute(const GLuint VAO, const size_t index)
    {
        glDisableVertexArrayAttrib(VAO, index);
    }
*/
}

