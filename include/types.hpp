#pragma once

#include <chrono>

namespace ogl
{
    using DeltaTime = std::chrono::seconds;

    class Window;
    class App;

    class Shader;
    class VertexShader;
    class GeometryShader;
    class FragmentShader;
    
    class Object;

    class VertexAttributes;
    class Data;
    class Renderer;

    class VertexBuffer;
    class StaticVertexBuffer;
    class DynamicVertexBuffer;
} 