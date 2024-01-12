#pragma once

#include <expected>
#include <map>
#include <vector>
#include <span>
#include <concepts>
#include <cstring>
#include <functional>

namespace ogl
{
    template <typename Key, typename DataType>
    class ContiguousMappedStorage
    {
        public:
            struct ItemInfo
            {
                size_t size;
                size_t offset;
            };

            class ConstIterator
            {
                public:
                    using ConstMapIterator = std::map<Key, ItemInfo>::const_iterator;

                    struct Data
                    {
                        Key      key;
                        ItemInfo item_info;
                        
                        std::reference_wrapper<DataType> data;
                    };

                    ConstIterator(
                        const ContiguousMappedStorage& storage,
                        const ConstMapIterator& it     
                    )
                    :
                        storage{storage},
                        items_iterator{it}
                    {
                        updateData(); 
                    }

                    const Data* operator->() const
                    {
                        return &data;
                    }

                    const Data& operator*() const
                    {
                        return data;
                    }

                    bool operator==(const ConstIterator& it) const
                    {
                        return items_iterator == it.items_iterator;
                    }

                    bool operator!=(const ConstIterator& it) const
                    {
                        return items_iterator != it.items_iterator;
                    }

                    ConstIterator& operator++()
                    {
                        ++items_iterator;

                        updateData();

                        return *this;
                    }

                private:
                    const ContiguousMappedStorage& storage;
                    ConstMapIterator         items_iterator;

                    Data data;

                    void updateData()
                    {
                        data.key       = items_iterator->first;
                        data.item_info = items_iterator->second;

                        data.data = std::span<const DataType>{
                            storage.getData() + data.item_info.offset,
                            data.item_info.size
                        };
                    }
            };

            void set   (const Key& key, const DataType& data);
            void remove(const Key& key);

            ItemInfo getInfo(const Key& key);

                  DataType& operator[](const Key& key);
            const DataType& operator[](const Key& key) const;

                  DataType* getData();
            const DataType* getData() const;
            
            size_t getSize()                     const;
            size_t getSizeExcept(const Key& key) const;
            
            size_t getOffset(const Key& key) const;

            ConstIterator begin() const;
            ConstIterator end()   const;

        protected:
            std::map   <Key, ItemInfo> items;
            std::vector<DataType>      data;

            void moveItemsFrom(const Key& key, long long space);
            Key  getKeyBefore (const Key& key);
    };
}

#include "contiguous_mapped_storage.tpp"