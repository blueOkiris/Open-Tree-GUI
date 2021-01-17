#pragma once

#include <memory>
#include <SFML/Window.hpp>
#include <Widget.hpp>
#include <Containers.hpp>
#include <Utility.hpp>

namespace opentree {
    class Window {
        private:
            sf::RenderWindow _window;
            WindowContainer _root;
        
        public:
            Window(const Vector2 &size, const std::string &title);
            void addWidget(std::shared_ptr<IWidget> child);
            std::shared_ptr<IWidget> root();
            void run();
    };
}
