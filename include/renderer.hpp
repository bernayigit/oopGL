#pragma once

#include <unordered_map>

#include "shaders/vertex_shader.hpp"
#include "shaders/geometry_shader.hpp"
#include "shaders/fragment_shader.hpp"

#include "objects/object.hpp"
#include "objects/indexed_object.hpp"

namespace ogl
{ 
    class Renderer
    {
        public:
            Renderer();

            Renderer& operator<<(const Object& object);
            Renderer& operator<<(const IndexedObject& object);

            bool addVertexShader(const VertexShader& shader, const std::string& name);
            bool removeVertexShader(const std::string& name);
            VertexShader& getVertexShader(const std::string& name);
            bool useVertexShader(const std::string& name);
            VertexShader& getActiveVertexShader();

            bool isUsingVertexShader(const std::string_view name);

            #ifdef GEOM_SHADER
            bool addGeometryShader(const GeometryShader& shader, const std::string& name);
            bool removeGeometryShader(const std::string& name);
            Geometry& getGeometryShader(const std::string& name);
            #endif

            bool addFragmentShader(const FragmentShader& shader, const std::string& name);
            bool removeFragmentShader(const std::string& name);
            FragmentShader& getFragmentShader(const std::string& name);
            bool useFragmentShader(const std::string& name);
            FragmentShader& getActiveFragmentShader();

            bool isUsingFragmentShader(const std::string_view name);

        protected:
            std::unordered_map<std::string, VertexShader>  vertex_shaders;
            #ifdef GEOM_SHADER
            std::unordered_map<std::string, GeometryShader> geometry_shaders;
            #endif
            std::unordered_map<std::string, FragmentShader> fragment_shaders;

            struct ActiveShaders
            {
                std::string vertex_shader;
                std::string geometry_shader;
                std::string fragment_shader;
            } active_shaders;

            GLuint last_used_VAO;
    };
}

#include "renderer.tpp"