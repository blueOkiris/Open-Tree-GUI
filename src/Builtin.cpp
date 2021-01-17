#include <iostream>
#include <SFML/Graphics.hpp>
#include <Widget.hpp>
#include <Builtin.hpp>

using namespace opentree;

ColorRect::ColorRect(
        uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha) :
        _color(red, green, blue, alpha) {
}

void ColorRect::setDrawRect(const Rect drawRect) {
    _drawRect = drawRect;
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
    sf::RectangleShape rect({
        static_cast<float>(_drawRect.w), static_cast<float>(_drawRect.h)
    });
    rect.setPosition(
        static_cast<float>(_drawRect.x), static_cast<float>(_drawRect.y)
    );

    rect.setFillColor(_color);
    target.draw(rect);
}
