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
    auto children = getChildren();
    for(auto child : children) {
        child->onKeyPressed(
            code, altPressed, ctrlPressed, shiftPressed, systemPressed
        );
    }
}

void Container::onKeyReleased(
        sf::Keyboard::Key code,
        bool altPressed, bool ctrlPressed, bool shiftPressed,
        bool systemPressed) {
    auto children = getChildren();
    for(auto child : children) {
        child->onKeyReleased(
            code, altPressed, ctrlPressed, shiftPressed, systemPressed
        );
    }
}

void Container::onMouseButtonPressed(sf::Mouse::Button button, int x, int y) {
    auto children = getChildren();
    for(auto child : children) {
        child->onMouseButtonPressed(button, x, y);
    }
}

void Container::onMouseButtonReleased(sf::Mouse::Button button, int x, int y) {
    auto children = getChildren();
    for(auto child : children) {
        child->onMouseButtonReleased(button, x, y);
    }
}

void Container::onMouseMoved(int x, int y) {
    auto children = getChildren();
    for(auto child : children) {
        child->onMouseMoved(x, y);
    }
}

void Container::onMouseScrolled(
        sf::Mouse::Wheel wheel, float delta, int x, int y) {
    auto children = getChildren();
    for(auto child : children) {
        child->onMouseScrolled(wheel, delta, x, y);
    }
}

void Container::onWindowResized(unsigned int width, unsigned int height) {
    auto children = getChildren();
    for(auto child : children) {
        child->onWindowResized(width, height);
    }
}

void Container::onTextEntered(uint32_t character) {
    auto children = getChildren();
    for(auto child : children) {
        child->onTextEntered(character);
    }
}

BasicContainer::BasicContainer(
        const std::shared_ptr<IWidget> &parent, sf::RenderWindow &window) :
        _parent(parent), _window(window) {
}

std::shared_ptr<IWidget> BasicContainer::getParent() {
    return _parent;
}

std::vector<std::shared_ptr<IWidget>> BasicContainer::getChildren() {
    return _children;
}

void BasicContainer::addChild(std::shared_ptr<IWidget> child) {
    _children.push_back(child);
}

void BasicContainer::draw(
        sf::RenderTarget &target, sf::RenderStates states) const {
    for(auto child : _children) {
        target.draw(*std::dynamic_pointer_cast<Drawable>(child).get());
    }
}

Rect BasicContainer::getDrawRect() {
    if(_parent != nullptr) {
        return _parent->getDrawRect();
    } else {
        return { 0, 0, _window.getSize().x, _window.getSize().y };
    }
}
