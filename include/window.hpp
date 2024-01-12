#pragma once

#include <SFML/Window.hpp>
#include <string_view>
#include <memory>
#include <chrono>

#include "glm/glm.hpp"

#include "types.hpp"

namespace ogl
{
    class Window : public sf::Window, public std::enable_shared_from_this<Window> 
    {
        public:
            Window(
                App&                app,
                const sf::VideoMode mode, 
                const std::string&  title,
                const uint32_t      style,
                const glm::vec3     clear_color = {}
            );

            Window(
                const sf::VideoMode mode, 
                const std::string&  title,
                const uint32_t      style,
                const sf::ContextSettings& setts,
                const glm::vec3     clear_color = {}
            );

            using sf::Window::Window;

            virtual void processInput(const DeltaTime delta_time = {});
            virtual void onResize    ();
            virtual void clear       ();
            virtual void draw        (const DeltaTime delta_time = {}) = 0;

            void      setClearColor( const glm::vec3 clear_color);
            glm::vec3 getClearColor();

            virtual void update(const DeltaTime delta_time = {});

            virtual ~Window();

            bool isRunning();

        protected:
            bool running {true};

            glm::vec3 clear_color;
    };
}