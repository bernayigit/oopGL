#pragma once

#include <SFML/Window.hpp>

#include <unordered_map>
#include <memory>
#include <chrono>

#include "types.hpp"

namespace ogl
{
    class App
    {
        public:
            friend class Window;

            App(const sf::ContextSettings& settings);

            virtual void update(const DeltaTime delta_time = {});
        
            bool addWindow(const std::shared_ptr<Window> window, const std::string& name);
            bool removeWindow(const std::string&name);

            const sf::ContextSettings& getContextSettings() const;
        
        protected:
            sf::ContextSettings context_setts;

            std::unordered_map<std::string, std::shared_ptr<Window>> windows;

            bool first_window {true};

            void updateWindows(const DeltaTime delta_time = {});
    };

}