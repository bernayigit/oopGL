#include "window.hpp"

#include "GL/glew.h"

#include "app.hpp"

namespace ogl
{
    Window::Window(
        App &app, const sf::VideoMode mode, const std::string &title,
        const uint32_t style, const glm::vec3 clear_color
    )
    :
        sf::Window{mode, title, style, app.getContextSettings()}, clear_color{clear_color}
    {
    }

    Window::Window(
        const sf::VideoMode mode, const std::string &title,
        const uint32_t style, const sf::ContextSettings &setts,
        const glm::vec3 clear_color
    )
    :
        sf::Window{mode, title, style, setts}, clear_color{clear_color}
    {
    }

    void Window::processInput(const DeltaTime delta_time)
    {
        sf::Event event;

        while(pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
            {
                running = false;
            } else 
            if(event.type == sf::Event::Resized)
            {
                onResize();
            }
        }
    }

    void Window::onResize()
    {
        glViewport(0, 0, getSize().x, getSize().y);
    }

    void Window::clear()
    {
        glClearColor(
            clear_color.r,
            clear_color.g,
            clear_color.b,
            0.0f
        );
        glClear(GL_COLOR_BUFFER_BIT);
    }

    bool Window::isRunning()
    {
        return running;
    }

    glm::vec3 Window::getClearColor()
    {
        return clear_color;
    }

    void Window::update(const DeltaTime delta_time)
    {
        processInput(delta_time);
        clear();
        draw(delta_time);
        display();
    }

    Window::~Window()
    {
    }
}
    