#pragma once 

#include "shader.hpp"

namespace ogl
{
    class VertexShader : public Shader
    {
        public:   
            VertexShader(const std::optional<std::filesystem::path> path = {});

            Result use() const override;

        protected:
    };
}