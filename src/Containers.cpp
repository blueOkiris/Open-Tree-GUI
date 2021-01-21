#include <vector>
#include <memory>
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include <Widget.hpp>
#include <Utility.hpp>
#include <Containers.hpp>

using namespace opentree;

void IContainer::onKeyPressed(
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

void IContainer::onKeyReleased(
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

void IContainer::onMouseButtonPressed(sf::Mouse::Button button, int x, int y) {
    auto childs = children();
    for(auto child : childs) {
        child->onMouseButtonPressed(button, x, y);
    }
}

void IContainer::onMouseButtonReleased(sf::Mouse::Button button, int x, int y) {
    auto childs = children();
    for(auto child : childs) {
        child->onMouseButtonReleased(button, x, y);
    }
}

void IContainer::onMouseMoved(int x, int y) {
    auto childs = children();
    for(auto child : childs) {
        child->onMouseMoved(x, y);
    }
}

void IContainer::onMouseScrolled(
        sf::Mouse::Wheel wheel, float delta, int x, int y) {
    auto childs = children();
    for(auto child : childs) {
        child->onMouseScrolled(wheel, delta, x, y);
    }
}

void IContainer::onWindowResized(unsigned int width, unsigned int height) {
    auto childs = children();
    for(auto child : childs) {
        child->onWindowResized(width, height);
    }
}

void IContainer::onTextEntered(uint32_t character) {
    auto childs = children();
    for(auto child : childs) {
        child->onTextEntered(character);
    }
}

WindowContainer::WindowContainer(sf::RenderWindow &window) : _window(window) {
}

void WindowContainer::setDrawRect(const Rect drawRect) {
}

std::vector<IWidgetPtr> WindowContainer::children() {
    return _children;
}

void WindowContainer::addChild(IWidgetPtr child) {
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

IWidgetPtr MarginContainer::create(const AttributeSet &attr) {
    /*
     * Should have one attribute "margin"
     * which is a comma delimited set like margin="0,0,0,0"
     * 
     * Whitespace shouldn't matter and everything should be integer
     * Also program shouldn't fail on error, simply print message to console
     */
    
    Rect marginRect = { 0, 0, 0, 0 };
    
    for(const auto attrPair : attr) {
        if(attrPair.first == "margin") {
            auto numStrs = strsplit(attrPair.second, ',');

            std::vector<int> numbers;
            for(const auto numStr : numStrs) {
                try {
                    int value = std::stoi(numStr, nullptr);
                    numbers.push_back(value);
                } catch(...) {
                    std::cout
                        << "Unknown value in margin container margin: "
                        << attrPair.second
                        << std::endl;
                }
            }
            
            if(numbers.size() > 0) {
                marginRect.x = numbers[0];
            }
            if(numbers.size() > 1) {
                marginRect.y = numbers[1];
            }
            if(numbers.size() > 2) {
                marginRect.w = numbers[2];
            }
            if(numbers.size() > 3) {
                marginRect.h = numbers[3];
            }
        } else {
            std::cout
                << "Unknown margin container attribute: " << attrPair.first
                << std::endl;
        }
    }
    
    return std::make_shared<MarginContainer>(marginRect);
}

void MarginContainer::setDrawRect(const Rect drawRect) {
    _drawRect = drawRect;
}

std::vector<IWidgetPtr> MarginContainer::children() {
    return _children;
}

void MarginContainer::addChild(IWidgetPtr child) {
    _children.push_back(child);
}

void MarginContainer::draw(
        sf::RenderTarget &target, sf::RenderStates states) const {
    Rect childRect = {
        _drawRect.x + _marginRect.x, _drawRect.y + _marginRect.y,
        _drawRect.w - _marginRect.w - _marginRect.x,
        _drawRect.h - _marginRect.h - _marginRect.y
    };
    for(auto child : _children) {
        child->setDrawRect(childRect);
        target.draw(*std::dynamic_pointer_cast<Drawable>(child).get());
    }
}

HBoxContainer::HBoxContainer(int separation) : _separation(separation) {
}

IWidgetPtr HBoxContainer::create(const AttributeSet &attr) {
    int separation = 0;
    
    for(const auto attrPair : attr) {
        if(attrPair.first == "separation") {
            try {
                int value = std::stoi(attrPair.second, nullptr);
                separation = value;
            } catch(...) {
                std::cout
                    << "Unknown value in horizontal box container separation: "
                    << attrPair.second
                    << std::endl;
            }
        } else {
            std::cout
                << "Unknown horizontal box container attribute: "
                << attrPair.first
                << std::endl;
        }
    }
        
    return std::make_shared<HBoxContainer>(separation);
}

void HBoxContainer::setDrawRect(const Rect drawRect) {
    _drawRect = drawRect;
}

std::vector<IWidgetPtr> HBoxContainer::children() {
    return _children;
}

void HBoxContainer::addChild(IWidgetPtr child) {
    _children.push_back(child);
}

void HBoxContainer::draw(
        sf::RenderTarget &target, sf::RenderStates states) const {
    for(size_t i = 0; i < _children.size(); i++) {
        unsigned int index = static_cast<unsigned int>(i);
        unsigned int childnSz = static_cast<unsigned int>(_children.size());
        Rect childRect = {
            _drawRect.x +
                index * (_drawRect.w / childnSz) + index * _separation,
            _drawRect.y,
            _drawRect.w / childnSz - ((childnSz - 1) * _separation),
            _drawRect.h
        };
        _children[i]->setDrawRect(childRect);
        target.draw(*std::dynamic_pointer_cast<Drawable>(_children[i]).get());
    }
}

VBoxContainer::VBoxContainer(int separation) : _separation(separation) {
}

IWidgetPtr VBoxContainer::create(const AttributeSet &attr) {
    int separation = 0;
    
    for(const auto attrPair : attr) {
        if(attrPair.first == "separation") {
            try {
                int value = std::stoi(attrPair.second, nullptr);
                separation = value;
            } catch(...) {
                std::cout
                    << "Unknown value in vertical box container separation: "
                    << attrPair.second
                    << std::endl;
            }
        } else {
            std::cout
                << "Unknown vertical box container attribute: "
                << attrPair.first
                << std::endl;
        }
    }
    
    return std::make_shared<VBoxContainer>(separation);
}

void VBoxContainer::setDrawRect(const Rect drawRect) {
    _drawRect = drawRect;
}

std::vector<IWidgetPtr> VBoxContainer::children() {
    return _children;
}

void VBoxContainer::addChild(IWidgetPtr child) {
    _children.push_back(child);
}

void VBoxContainer::draw(
        sf::RenderTarget &target, sf::RenderStates states) const {
    for(size_t i = 0; i < _children.size(); i++) {
        unsigned int index = static_cast<unsigned int>(i);
        unsigned int childnSz = static_cast<unsigned int>(_children.size());
        Rect childRect = {
            _drawRect.x,
            _drawRect.y
                + index * (_drawRect.h / childnSz) + index * _separation,
            _drawRect.w,
            _drawRect.h / childnSz - ((childnSz - 1) * _separation),
        };
        _children[i]->setDrawRect(childRect);
        target.draw(*std::dynamic_pointer_cast<Drawable>(_children[i]).get());
    }
}
