#pragma once 

#include <type_traits>
#include <span>
#include <vector>

namespace ogl
{
    struct Data
    {
        template <typename T>
        Data(const std::span<T> data);

        template <typename T>
        void operator=(const std::span<T> data);

        template <typename T> 
        T& operator[](size_t index);

        template <typename T>
        std::span<T> getSpan();

        std::vector<std::byte> data;
        size_t element_size;
    };


}

#include "data.tpp"