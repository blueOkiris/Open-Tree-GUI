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
}

void Container::onKeyReleased(
        sf::Keyboard::Key code,
        bool altPressed, bool ctrlPressed, bool shiftPressed,
        bool systemPressed) {
}

void Container::onMouseButtonPressed(
        sf::Mouse::Button button, int x, int y) {
}

void Container::onMouseButtonReleased(
        sf::Mouse::Button button, int x, int y) {
}

void Container::onMouseMoved(int x, int y) {
}

void Container::onMouseScrolled(
        sf::Mouse::Wheel wheel, float delta, int x, int y) {
}

void Container::onWindowResized(
        unsigned int width, unsigned int height) {
}

void Container::onTextEntered(uint32_t character) {
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

void BasicContainer::draw(
        sf::RenderTarget &target, sf::RenderStates states) const {
    for(auto child : _children) {
        target.draw(*std::dynamic_pointer_cast<Drawable>(child).get());
    }
}

Rect BasicContainer::getDrawRect() {
    return _parent->getDrawRect();
}
