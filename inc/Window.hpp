#pragma once

#include <memory>
#include <SFML/Window.hpp>
#include <Containers.hpp>
#include <Utility.hpp>

namespace opentree {
    class Window {
        private:
            sf::RenderWindow _window;
            BasicContainer _root;
        
        public:
            Window(const Vector2 &size, const std::string &title);
            void run();
    };
}
