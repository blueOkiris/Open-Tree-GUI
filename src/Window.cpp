#include <memory>
#include <SFML/Window.hpp>
#include <Widget.hpp>
#include <Containers.hpp>
#include <Utility.hpp>
#include <Window.hpp>

using namespace opentree;

Window::Window(
        const Vector2 &size,  const Vector2 &minSize,
        const std::string &title) :
        _window(sf::VideoMode(size.x, size.y), title), _root(_window),
        _minSize(minSize) {
}

void Window::addWidget(std::shared_ptr<IWidget> child) {
    _root.addChild(child);
}

std::shared_ptr<IWidget> Window::root() {
    return std::make_shared<WindowContainer>(_root);
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
                    if(event.size.width < _minSize.x) {
                        _window.setSize(sf::Vector2u(
                            _minSize.x, _window.getSize().y
                        ));
                    }

                    if(event.size.height < _minSize.y) {
                        _window.setSize(sf::Vector2u(
                            _window.getSize().x, _minSize.y
                        ));
                    }

                    {
                        sf::View newView;
                        newView.reset(sf::FloatRect(
                            0, 0, event.size.width, event.size.height
                        ));
                        newView.setViewport(
                            sf::FloatRect(0, 0, 1, 1)
                        );
                        _window.setView(newView);
                    }
                    
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
