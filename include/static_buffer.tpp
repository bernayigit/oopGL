namespace ogl
{
    template <typename Key>
    StaticBuffer<Key>::StaticBuffer(const size_t size, GLbitfield flags)
    :
        size{size}
    {
        this->ids.resize(1);

        glCreateBuffers(1, &this->ids.front());

        glNamedBufferStorage(
            this->ids.front(),
            size,
            NULL,
            flags
        );
    }

    template <typename Key>
    bool StaticBuffer<Key>::set(const VertexAttributes& attribs)
    {
        if(this->buffer.getSizeExcept(&attribs) + attribs.getData().size() > size)
        {
            return false;
        } else 
        {
            for(auto it {this->items.lower_bound(&attribs)}; it != this->items.end(); ++it)
            {
                it->second.updated = false;
            }

            this->buffer.set(
                &attribs,
                std::vector<std::byte>{
                    attribs.getData().begin(),
                    attribs.getData().end()
                }
            );

            this->items[&attribs].stride = attribs.getStride();

            return true;
        }
    }

    template <typename Key>
    bool StaticBuffer<Key>::remove(const Key& key)
    {
        if(this->items.contains(key))
        {
            this->buffer.remove(key);
            this->items.erase(key);

            return true;
        } else 
        {
            return false;
        }
    }
    

    template <typename Key>
    void StaticBuffer<Key>::upload()
    {
        std::optional<size_t> start {};
        size_t                size  {};
        
        size_t item_offset {};

        for(const auto&[key, item, item_data] : this->buffer)
        {
            if(this->items[key].updated)
            {
                if(!start.has_value())
                {
                    start = item.offset;
                } 
                
                size += item.size;

                this->items[key].updated = false;
                this->items[key].offset  = item_offset;

                item_offset += item.size;
            } else 
            {
                if(start.has_value())
                {
                    glNamedBufferSubData(
                        this->ids.front(),
                        *start,
                        size,
                        this->buffer.getData()
                    );

                    size = 0;

                    start.reset();
                }
            }
        }
    }

    template <typename Key>
    StaticBuffer<Key>::~StaticBuffer()
    {
        glDeleteBuffers(1, &this->ids.front());
    }
}