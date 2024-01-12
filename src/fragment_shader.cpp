#include "fragment_shader.hpp"

namespace ogl
{
    FragmentShader::FragmentShader(const std::optional<std::filesystem::path> t_path)
    :
        Shader(Type::Fragment, t_path)
    {
    }

    Shader::Result FragmentShader::use() const
    {
        shaders[2] = id;

        if(!shaders[0])
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