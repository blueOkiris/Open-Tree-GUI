#include <memory>
#include <SFML/Window.hpp>
#include <Widget.hpp>
#include <Containers.hpp>
#include <Utility.hpp>
#include <Window.hpp>

using namespace opentree;

Window::Window(const Vector2 &size, const std::string &title) :
        _window(sf::VideoMode(size.x, size.y), title),
        _root(nullptr, _window) {
}

void Window::addWidget(std::shared_ptr<IWidget> child) {
    _root.addChild(child);
}

std::shared_ptr<IWidget> Window::root() {
    return std::make_shared<BasicContainer>(_root);
}

void Window::run() {
    while(_window.isOpen()) {
        sf::Event event;
        while(_window.pollEvent(event)) {
            // Thread 1
            switch(event.type) {
                case sf::Event::Closed:
                    _window.close();
                    break;
                    
                case sf::Event::KeyPressed:
                    _root.onKeyPressed(
                        event.key.code, event.key.alt, event.key.control,
                        event.key.shift, event.key.system
                    );
                    break;
                    
                case sf::Event::KeyReleased:
                    _root.onKeyReleased(
                        event.key.code, event.key.alt, event.key.control,
                        event.key.shift, event.key.system
                    );
                    break;
                
                case sf::Event::MouseButtonPressed:
                    _root.onMouseButtonPressed(
                        event.mouseButton.button,
                        event.mouseButton.x, event.mouseButton.y
                    );
                    break;
                
                case sf::Event::MouseButtonReleased:
                    _root.onMouseButtonReleased(
                        event.mouseButton.button,
                        event.mouseButton.x, event.mouseButton.y
                    );
                    break;
                
                case sf::Event::MouseMoved:
                    _root.onMouseMoved(event.mouseMove.x, event.mouseMove.y);
                    break;
                
                case sf::Event::MouseWheelScrolled:
                    _root.onMouseScrolled(
                        event.mouseWheelScroll.wheel,
                        event.mouseWheelScroll.delta,
                        event.mouseWheelScroll.x, event.mouseWheelScroll.y
                    );
                    break;
                
                case sf::Event::TextEntered:
                    _root.onTextEntered(event.text.unicode);
                    break;
                
                case sf::Event::Resized:
                    _root.onWindowResized(event.size.width, event.size.height);
                    break;
                
                default:
                    break;
            }
        }
        
        _window.clear();
        _window.draw(_root);
        _window.display();
    }
}
