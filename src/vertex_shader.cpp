#include "vertex_shader.hpp"
#include "fragment_shader.hpp"

namespace ogl
{
    VertexShader::VertexShader(const std::optional<std::filesystem::path> t_path)
    :
        Shader(Type::Vertex, t_path)
    {
    }

    Shader::Result VertexShader::use() const 
    {
        shaders[0] = id;

        if(!shaders[2])
        {
            return {ResultCode::shader_set};
        }

        if(program)
        {
            glDeleteProgram(*program);
        }

        program = glCreateProgram();

        glAttachShader(*program, *shaders[0]);
        glAttachShader(*program, *shaders[2]);

        glLinkProgram(*program);

        int success;

        glGetProgramiv(*program, GL_LINK_STATUS, &success);

        Result result {ResultCode::success};

        if(!success)
        {
            char log[log_size];

            glGetProgramInfoLog(*program, log_size, NULL, log);

            result.code          = ResultCode::cannot_link;
            result.error_message = log;
        } else 
        {
            glUseProgram(*program);
        }

        return result;
    }
}