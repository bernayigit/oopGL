#include "app.hpp"

#include "GL/glew.h"

#include "window.hpp"

#include <iostream>

namespace ogl
{    
    App::App(const sf::ContextSettings& setts)
    :
        context_setts(setts)
    {
    }

    void App::update(const DeltaTime delta_time)
    {
        updateWindows(delta_time);
    }

    bool App::addWindow(const std::shared_ptr<Window> window, const std::string& name)
    {
        if(windows.contains(name))
        {
            return false;
        } else 
        {
            windows[name] = window;

            if(first_window)
            {
                //glewInit();

                first_window = false;
            }

            return true;
        }
    }

    bool App::removeWindow(const std::string& name)
    {
        if(windows.contains(name))
        {
            windows.erase(name);
            
            return true;
        } else 
        {
            return false;
        }
    }

    const sf::ContextSettings &App::getContextSettings() const
    {
        return context_setts;
    }

    void App::updateWindows(const DeltaTime delta_time)
    {
        for(auto&[name, window] : windows)
        {
            if(!window->isRunning())
            {
                windows.erase(name);

                return;
            }

            window->setActive();
            window->update(delta_time);
        }
    }
}