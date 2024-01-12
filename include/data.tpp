#include <cstring>

namespace ogl
{
    template <typename T>
    Data::Data(const std::span<T> t_data)
    :
        data{t_data}, element_size{sizeof(T)}
    {
    }

    template <typename T>
    void Data::operator=(const std::span<T> t_data)
    {
        memcpy(data.data(), data.data(), data.size());
    }

    template <typename T>
    T& Data::operator[](size_t index)
    {
        return static_cast<T&>(*(data.data() + (index * element_size)));
    }

    template <typename T>
    std::span<T> Data::getSpan()
    {
        return std::span<T>(data.data(), data.size());
    }
}