#include <stdexcept>
#include <iostream>

namespace ogl
{
    template<typename Key, typename DataType>
    typename ContiguousMappedStorage<Key, DataType>::ItemInfo
    ContiguousMappedStorage<Key, DataType>::getInfo(const Key& key)
    {
        if(items.contains(key))
        {
            return items[key];
        } else 
        {
            throw std::out_of_range{"Key not found"};
        }
    }

    template<typename Key, typename DataType>
    void ContiguousMappedStorage<Key, DataType>::set(const Key& key, const DataType& t_data)
    {
        if(items.empty())
        {
            data.reserve(1);
        }

        if(items.contains(key) && data.size() > items[key].size)
        {
            moveItemsFrom(key, data.size());
        } else 
        {
            moveItemsFrom(getKeyBefore(key), data.size());
        }

        std::cin.get();
        
        items[key].size       = data.size();
        this->operator[](key) = data;
    }

    template<typename Key, typename DataType>
    Key ContiguousMappedStorage<Key, DataType>::getKeyBefore(const Key& key)
    {
        Key before_key {};

        for(const auto&[k, item_data] : items)
        {
            if(k >= key)
            {
                break;
            } else 
            {
                before_key = k;
            }
        }

        return before_key;
    }

    template<typename Key, typename DataType>
    void ContiguousMappedStorage<Key, DataType>::moveItemsFrom(const Key& key, const long long space)
    {
        // Allocate new space
        data.reserve(data.size() + space);

        const auto offset {getOffset(key)};

        // Copy old memory section in new one
        memcpy(
            data.data() + offset + space,
            data.data() + offset,
            data.size() - offset    
        );

        // Update items offsets
        for(auto i {++items.lower_bound(key)}; i != items.end(); ++i)
        {
            i->second.offset += space;
        }
    }

    template<typename Key, typename DataType>
    size_t ContiguousMappedStorage<Key, DataType>::getOffset(const Key& key) const 
    {
        if(items.contains(key))
        {
            return items.at(key).offset;
        } else 
        {
            throw std::out_of_range{"Key not found"};
        }
        
    }

    template<typename Key, typename DataType>
    void ContiguousMappedStorage<Key, DataType>::remove(const Key& key)
    {
        if(items.contains(key))
        {
            moveItemsFrom(key, -items.at(key).size);
            items.erase(key);
        } else 
        {
            throw std::out_of_range{"Key not found"};
        }
    }

    template <typename Key, typename DataType>
    const DataType* ContiguousMappedStorage<Key, DataType>::getData() const
    {
        return data.data();
    }

    template <typename Key, typename DataType>
    DataType* ContiguousMappedStorage<Key, DataType>::getData()
    {
        return data.data();
    }    

    template<typename Key, typename DataType>
    size_t ContiguousMappedStorage<Key, DataType>::getSize() const
    {
        return data.size();
    }

    template <typename Key, typename DataType>
    DataType& ContiguousMappedStorage<Key, DataType>::operator[](const Key& key)
    {
        if(items.contains(key))
        {
            return *(data.data() + getOffset(key));
        } else 
        {
            throw std::out_of_range{"Key not found"};
        }
    }

    template<typename Key, typename DataType>
    size_t ContiguousMappedStorage<Key, DataType>::getSizeExcept(const Key& key) const
    {
        size_t size {getSize()};

        if(items.contains(key))
        {
            size -= items.at(key).size;
        } 

        return size;
    }

    template <typename Key, typename DataType>
    inline ContiguousMappedStorage<Key, DataType>::ConstIterator
        ContiguousMappedStorage<Key, DataType>::begin() const
    {
        return {*this, items.begin()};
    }    

    template <typename Key, typename DataType>
    inline ContiguousMappedStorage<Key, DataType>::ConstIterator
        ContiguousMappedStorage<Key, DataType>::end() const
    {
        return {*this, items.end()};
    }      
}