#include <iostream>
#include <SFML/Graphics.hpp>
#include <Widget.hpp>
#include <Builtin.hpp>

using namespace opentree;

ColorRect::ColorRect(
        uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha) :
        _color(red, green, blue, alpha) {
}

IWidgetPtr ColorRect::create(const AttributeSet &attr) {
    /*
     * Should have one attr "color"
     * color = "#--------"
     * Each section is a hex code for a byte
     */
    uint8_t red = 0, green = 0, blue = 0, alpha = 0;  
    
    for(const auto attrPair : attr) {
        if(attrPair.first == "color") {
            if(attrPair.second[0] == '#' && attrPair.second.length() == 9) {
                try {
                    red = std::stoi(attrPair.second.substr(1, 2), nullptr, 16);
                    green = std::stoi(
                        attrPair.second.substr(3, 2), nullptr, 16
                    );
                    blue = std::stoi(attrPair.second.substr(5, 2), nullptr, 16);
                    alpha = std::stoi(
                        attrPair.second.substr(7, 2), nullptr, 16
                    );
                } catch(...) {
                    std::cout
                        << "Unknown value in color rect separation: "
                        << attrPair.second << std::endl;
                }
            } else {
                std::cout
                    << "Color rect color in incorrect format: "
                    << attrPair.second << std::endl;
            }
        } else {
            std::cout
                << "Unknown color rect attribute: "
                << attrPair.first << std::endl;
        }
    }  
    
    return std::make_shared<ColorRect>(red, green, blue, alpha);
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
