#include "shader.hpp"

#include <fstream>
#include <sstream>

namespace ogl
{
    Shader::Shader(const Type type, const std::optional<std::filesystem::path> t_path)
    :   
        path(t_path.value_or("")), source{}, status(load(path)), type{type}
    {
    }

    Shader::Result Shader::load(const std::optional<std::filesystem::path> t_path)
    {
        // If user provided a path, 
        if(t_path)
        {
            path = *t_path;
        }

        using namespace std;

        // Check if file exists
        if(!filesystem::exists(path))
        {
            return {
                ResultCode::cannot_find
            };
        }

        // Try to open file
        ifstream file {path};

        // Check if file is open
        if(!file.is_open())
        {
            return ResultCode::cannot_open;
        }

        // Load file into source member variable
        source = (stringstream{} << file.rdbuf()).str();

        // Close file
        file.close();

        // Set result member variable and return it
        return ResultCode::success;
    }

    Shader::Result Shader::compile(const std::optional<std::filesystem::path> t_path)
    {
        // Optionally load
        if(t_path)
        {
            load(t_path);
        }

        // If couldn't load, return error
        if(status.code != ResultCode::success)
        {
            return status;
        }

        // Compile
        
        GLenum shader_type {
            static_cast<GLenum>(
                type == Type::Vertex ? 
                GL_VERTEX_SHADER : GL_FRAGMENT_SHADER
            )
        };

        const char* source_c_str {source.c_str()};

        id = glCreateShader(shader_type);

        glShaderSource(id, 1, &source_c_str, NULL);
        glCompileShader(id);

        // Check status

        int success;

        glGetShaderiv(id, GL_COMPILE_STATUS, &success);

        Result result {ResultCode::success};

        if(!success)
        {
            char log[log_size];

            glGetShaderInfoLog(id, log_size, NULL, log);

            result.code          = ResultCode::cannot_compile;
            result.error_message = log;
        } 

        return status = result;
    }

    Shader::Result Shader::getStatus() const
    {
        return status;
    }

    GLuint Shader::getId() const
    {
        return id;
    }

    Shader::Result::Result(const ResultCode code, const std::string_view msg)
    :
        code(code), error_message(msg)
    {
    }

    std::array<std::optional<GLuint>, 3> Shader::shaders {
        std::nullopt,
        std::nullopt,
        std::nullopt
    };

    std::optional<GLuint> Shader::program {std::nullopt};

    Shader::~Shader()
    {
        glDeleteShader(id);
    }

    /*
    void Shader::checkIfProgramIsValid()
    {
        if(glIsProgram(*program) == GL_TRUE)
        {
            std::cout << "Program is program\n";
        } else 
        {
            std::cout << "Program isn't\n";
        }
    }
    */
}
