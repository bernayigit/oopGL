#pragma once 

#include "shader.hpp"

namespace ogl
{
    class FragmentShader : public Shader
    {
        public:   
            FragmentShader(const std::optional<std::filesystem::path> path = {});

            Result use() const override;
    };
}