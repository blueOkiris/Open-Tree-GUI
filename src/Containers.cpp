#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>
#include <Widget.hpp>
#include <Utility.hpp>
#include <Containers.hpp>

using namespace opentree;

void Container::onKeyPressed(
        sf::Keyboard::Key code,
        bool altPressed, bool ctrlPressed, bool shiftPressed,
        bool systemPressed) {
    auto childs = children();
    for(auto child : childs) {
        child->onKeyPressed(
            code, altPressed, ctrlPressed, shiftPressed, systemPressed
        );
    }
}

void Container::onKeyReleased(
        sf::Keyboard::Key code,
        bool altPressed, bool ctrlPressed, bool shiftPressed,
        bool systemPressed) {
    auto childs = children();
    for(auto child : childs) {
        child->onKeyReleased(
            code, altPressed, ctrlPressed, shiftPressed, systemPressed
        );
    }
}

void Container::onMouseButtonPressed(sf::Mouse::Button button, int x, int y) {
    auto childs = children();
    for(auto child : childs) {
        child->onMouseButtonPressed(button, x, y);
    }
}

void Container::onMouseButtonReleased(sf::Mouse::Button button, int x, int y) {
    auto childs = children();
    for(auto child : childs) {
        child->onMouseButtonReleased(button, x, y);
    }
}

void Container::onMouseMoved(int x, int y) {
    auto childs = children();
    for(auto child : childs) {
        child->onMouseMoved(x, y);
    }
}

void Container::onMouseScrolled(
        sf::Mouse::Wheel wheel, float delta, int x, int y) {
    auto childs = children();
    for(auto child : childs) {
        child->onMouseScrolled(wheel, delta, x, y);
    }
}

void Container::onWindowResized(unsigned int width, unsigned int height) {
    auto childs = children();
    for(auto child : childs) {
        child->onWindowResized(width, height);
    }
}

void Container::onTextEntered(uint32_t character) {
    auto childs = children();
    for(auto child : childs) {
        child->onTextEntered(character);
    }
}

WindowContainer::WindowContainer(sf::RenderWindow &window) : _window(window) {
}

void WindowContainer::setDrawRect(const Rect drawRect) {
}

std::vector<std::shared_ptr<IWidget>> WindowContainer::children() {
    return _children;
}

void WindowContainer::addChild(std::shared_ptr<IWidget> child) {
    _children.push_back(child);
}

void WindowContainer::draw(
        sf::RenderTarget &target, sf::RenderStates states) const {
    for(auto child : _children) {
        child->setDrawRect({ 0, 0, _window.getSize().x, _window.getSize().y });
        target.draw(*std::dynamic_pointer_cast<Drawable>(child).get());
    }
}

MarginContainer::MarginContainer(Rect margins) : _marginRect(margins) {
}

void MarginContainer::setDrawRect(const Rect drawRect) {
    _drawRect = drawRect;
}

std::vector<std::shared_ptr<IWidget>> MarginContainer::children() {
    return _children;
}

void MarginContainer::addChild(std::shared_ptr<IWidget> child) {
    _children.push_back(child);
}

void MarginContainer::draw(
        sf::RenderTarget &target, sf::RenderStates states) const {
    Rect childRect = {
        _marginRect.x, _marginRect.y,
        _drawRect.w - _marginRect.w - _marginRect.x,
        _drawRect.h - _marginRect.h - _marginRect.y
    };
    for(auto child : _children) {
        child->setDrawRect(childRect);
        target.draw(*std::dynamic_pointer_cast<Drawable>(child).get());
    }
}
