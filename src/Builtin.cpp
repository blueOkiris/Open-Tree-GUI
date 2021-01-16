#include <SFML/Graphics.hpp>
#include <Widget.hpp>
#include <Builtin.hpp>

using namespace opentree;

Rect NonContainer::drawRect() {
    return parent()->drawRect();
}

ColorRect::ColorRect(
        const std::shared_ptr<IWidget> &parent,
        uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha) :
        _parent(parent), _color(red, green, blue, alpha) {
}

std::shared_ptr<IWidget> ColorRect::parent() {
    return _parent;
}

void ColorRect::onKeyPressed(
        sf::Keyboard::Key code,
        bool altPressed, bool ctrlPressed, bool shiftPressed,
        bool systemPressed) {
}
void ColorRect::onKeyReleased(
        sf::Keyboard::Key code,
        bool altPressed, bool ctrlPressed, bool shiftPressed,
        bool systemPressed) {
}
void ColorRect::onMouseButtonPressed(sf::Mouse::Button button, int x, int y) {
}
void ColorRect::onMouseButtonReleased(sf::Mouse::Button button, int x, int y) {
}
void ColorRect::onMouseMoved(int x, int y) {
}
void ColorRect::onMouseScrolled(
        sf::Mouse::Wheel wheel, float delta, int x, int y) {
}
void ColorRect::onWindowResized(unsigned int width, unsigned int height) {
}
void ColorRect::onTextEntered(uint32_t character) {
}

void ColorRect::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    auto rect = _parent->drawRect();
    sf::RectangleShape drawRect({
        static_cast<float>(rect.w), static_cast<float>(rect.h)
    });
    drawRect.setPosition(
        static_cast<float>(rect.x), static_cast<float>(rect.y)
    );
    drawRect.setFillColor(_color);
    target.draw(drawRect);
}
