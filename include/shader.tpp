#pragma once

#include <glm/glm.hpp>

#include <iostream>

namespace ogl
{
    template <typename T>
    bool Shader::setUniform(const std::string_view name, const T value)
    {
        GLint position {glGetUniformLocation(*program, name.data())};

        if(position == -1)
        {
            return false;
        } else 
        {
            if constexpr(std::is_same_v<T, glm::vec4>)
            {
                glUniform4f(position, value.x, value.y, value.z, value.w);
            }

            return true;
        }
    } 
}