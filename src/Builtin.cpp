#include <iostream>
#include <SFML/Graphics.hpp>
#include <Utility.hpp>
#include <Widget.hpp>
#include <Builtin.hpp>

using namespace opentree;

ColorRect::ColorRect(const Color &color) :
        _color(color.red, color.green, color.blue, color.alpha) {
}

IWidgetPtr ColorRect::create(
        const AttributeSet &attr, const FunctionSet &funcs) {
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
                        << "Unknown value in color rect color: "
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
    
    return std::make_shared<ColorRect>(Color { red, green, blue, alpha });
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

Button::Button(
        const Color &base, const Color &hover, const Color &pressed,
        const Color &baseFontColor, const Color &hoverFontColor,
        const Color &pressedFontColor,
        const sf::Font font,  const std::string &text,
        const CallBackFunc &callBack) :
        _baseColor(base.red, base.green, base.blue, base.alpha),
        _hoverColor(hover.red, hover.green, hover.blue, hover.alpha),
        _pressedColor(pressed.red, pressed.green, pressed.blue, pressed.alpha),
        _baseFontColor(
            baseFontColor.red, baseFontColor.green, baseFontColor.blue,
            baseFontColor.alpha
        ), _hoverFontColor(
            hoverFontColor.red, hoverFontColor.green, hoverFontColor.blue,
            hoverFontColor.alpha
        ), _pressedFontColor(
            pressedFontColor.red, pressedFontColor.green, pressedFontColor.blue,
            pressedFontColor.alpha
        ), _font(font), _text(text), _callBack(callBack),
        _state(ButtonState::Normal) {
}

IWidgetPtr Button::create(
        const AttributeSet &attr, FunctionSet funcs) {
    Color base, hover, pressed;
    Color baseFont, hoverFont, pressedFont;
    CallBackFunc callBack = [](IWidgetPtr self) { };
    std::string text;
    sf::Font font;
    
    for(const auto attrPair : attr) {
        if(attrPair.first == "base-color"
                || attrPair.first == "hover-color"
                || attrPair.first == "pressed-color"
                || attrPair.first == "font-base-color"
                || attrPair.first == "font-hover-color"
                || attrPair.first == "font-pressed-color") {
            if(attrPair.second[0] == '#' && attrPair.second.length() == 9) {
                Color value = { 0, 0, 0, 0 };
                try {
                    value.red = std::stoi(
                        attrPair.second.substr(1, 2), nullptr, 16
                    );
                    value.green = std::stoi(
                        attrPair.second.substr(3, 2), nullptr, 16
                    );
                    value.blue = std::stoi(
                        attrPair.second.substr(5, 2), nullptr, 16
                    );
                    value.alpha = std::stoi(
                        attrPair.second.substr(7, 2), nullptr, 16
                    );
                } catch(...) {
                    std::cout
                        << "Unknown value in button base color: "
                        << attrPair.second << std::endl;
                }
                
                if(attrPair.first == "base-color") {
                    base = value;
                } else if(attrPair.first == "hover-color") {
                    hover = value;
                } else if(attrPair.first == "pressed-color") {
                    pressed = value;
                } else if(attrPair.first == "font-base-color") {
                    baseFont = value;
                } else if(attrPair.first == "font-hover-color") {
                    hoverFont = value;
                } else if(attrPair.first == "font-pressed-color") {
                    pressedFont = value;
                }
            } else {
                std::cout
                    << "Button base-color in incorrect format: "
                    << attrPair.second << std::endl;
            }
        } else if(attrPair.first == "on-click") {
            if(funcs.find(attrPair.second) == funcs.end()) {
                std::cout
                    << "Failed to attach function '" << attrPair.second
                    << "' to button!" << std::endl;
            } else {
                callBack = funcs[attrPair.second];
            }
        } else if(attrPair.first == "text") {
            text = attrPair.second;
        } else {
            std::cout
                << "Unknown base attribute: "
                << attrPair.first << std::endl;
        }
    }  
    
    return std::make_shared<Button>(
        base, hover, pressed, baseFont, hoverFont, pressedFont, font, text,
        callBack
    );
}


void Button::setDrawRect(const Rect drawRect) {
    _drawRect = drawRect;
}

void Button::onKeyPressed(
        sf::Keyboard::Key code,
        bool altPressed, bool ctrlPressed, bool shiftPressed,
        bool systemPressed) {
}
void Button::onKeyReleased(
        sf::Keyboard::Key code,
        bool altPressed, bool ctrlPressed, bool shiftPressed,
        bool systemPressed) {
}
void Button::onMouseButtonPressed(sf::Mouse::Button button, int x, int y) {
}
void Button::onMouseButtonReleased(sf::Mouse::Button button, int x, int y) {
}

void Button::onMouseMoved(int x, int y) {
    if(_state != ButtonState::Pressed) {
        if(x > static_cast<int>(_drawRect.x)
                && x < static_cast<int>(_drawRect.x + _drawRect.w)
                && y > static_cast<int>(_drawRect.y)
                && y < static_cast<int>(_drawRect.y + _drawRect.h)) {
            _state = ButtonState::Hovering;
        } else {
            _state = ButtonState::Normal;
        }
    }
}

void Button::onMouseScrolled(
        sf::Mouse::Wheel wheel, float delta, int x, int y) {
}
void Button::onWindowResized(unsigned int width, unsigned int height) {
}
void Button::onTextEntered(uint32_t character) {
}

void Button::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    sf::RectangleShape rect({
        static_cast<float>(_drawRect.w), static_cast<float>(_drawRect.h)
    });
    rect.setPosition(
        static_cast<float>(_drawRect.x), static_cast<float>(_drawRect.y)
    );
    
    switch(_state) {
        case ButtonState::Normal:
            rect.setFillColor(_baseColor);
            break;
        
        case ButtonState::Hovering:
            rect.setFillColor(_hoverColor);
            break;
            
        case ButtonState::Pressed:
            rect.setFillColor(_pressedColor);
            break;
    }
    
    target.draw(rect);
}
