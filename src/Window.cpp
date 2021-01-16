#include <memory>
#include <SFML/Window.hpp>
#include <Containers.hpp>
#include <Utility.hpp>
#include <Window.hpp>

using namespace opentree;

Window::Window(const Vector2 &size, const std::string &title) :
        _window(sf::VideoMode(size.x, size.y), title),
        _root(nullptr, _window) {
}

void Window::run() {
    while(_window.isOpen()) {
        sf::Event event;
        while(_window.pollEvent(event)) {
            if(event.type == sf::Event::Closed) {
                _window.close();
            }
        }
        
        _window.clear();
        _window.draw(_root);
        _window.display();
    }
}
