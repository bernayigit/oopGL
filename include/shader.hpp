#pragma once

#include <GL/glew.h>

#include <string>
#include <filesystem>
#include <optional>
#include <array>
#include <cstdint>

namespace ogl
{
    class Shader
    {
        public:
            enum class ResultCode
            {
                success			= 1,
                cannot_compile 	= 0,
                cannot_find		= 0,
                cannot_open		= 0,
                cannot_link		= 0,
                shader_set
            };

            struct Result
            {
				Result(const ResultCode code, const std::string_view msg = "");

                ResultCode  code;
                std::string error_message;
            };

            enum class Type : uint8_t
            {
                Vertex   = 0,
                Geometry = 1,
                Fragment = 2
            };

            Shader(const Type type, const std::optional<std::filesystem::path> path = std::nullopt);

            Result         load   (const std::optional<std::filesystem::path> path = std::nullopt);
            virtual Result compile(const std::optional<std::filesystem::path> path = std::nullopt);

            template <typename T>
            bool setUniform(const std::string_view name, const T value);

            Result getStatus() const;

            GLuint getId() const;

            //void checkIfProgramIsValid();

            virtual Result use() const = 0;

            virtual ~Shader();
        protected:
            std::filesystem::path path;
            std::string           source;
            Result                status;
            
            Type   type;
            
            GLuint id;

            static std::array<std::optional<GLuint>, 3> shaders;
            
            static std::optional<GLuint> program;

            static constexpr size_t log_size {512};
    };
}

#include "shader.tpp"
