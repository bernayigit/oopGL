#pragma once

#include "../contiguous_mapped_storage.hpp"
#include "../types.hpp"

#include <unordered_map>
#include <GL/glew.h>

namespace ogl
{
    template <typename Key = const VertexAttributes*, typename DataType = std::vector<std::byte>>
    class Buffer
    {
        public:
            using DataView = std::span<const DataType>;

            struct ItemInfo
            {
                bool   updated;
                size_t stride;
                size_t offset;
            };

            virtual void upload() = 0;

            virtual bool set   (const VertexAttributes& attribs) = 0;
            virtual bool remove(const Key& key)                  = 0;

            virtual size_t getOffset(const Key& key);
            
            virtual GLuint getId(const Key& key) const;

        protected:
            ContiguousMappedStorage<Key, DataType> buffer;

            std::map<Key, ItemInfo> items;

            std::vector<GLuint> ids;
    };

    template <typename Key, typename DataType>
    inline GLuint Buffer<Key, DataType>::getId(const Key& key) const
    {
        return ids[0];
    }

    template <typename Key, typename DataType>
    inline size_t Buffer<Key, DataType>::getOffset(const Key& key)
    {
        return items[key].offset;
    }

}