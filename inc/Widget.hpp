#pragma once

#include <memory>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <Utility.hpp>

namespace opentree {
    struct IWidget :
            public sf::Drawable, public std::enable_shared_from_this<IWidget> {
        virtual void setDrawRect(const Rect newRect) = 0;
        
        virtual void onKeyPressed(
            sf::Keyboard::Key code,
            bool altPressed, bool ctrlPressed, bool shiftPressed,
            bool systemPressed
        ) = 0;
        virtual void onKeyReleased(
            sf::Keyboard::Key code,
            bool altPressed, bool ctrlPressed, bool shiftPressed,
            bool systemPressed
        ) = 0;
        virtual void onMouseButtonPressed(
            sf::Mouse::Button button, int x, int y
        ) = 0;
        virtual void onMouseButtonReleased(
            sf::Mouse::Button button, int x, int y
        ) = 0;
        virtual void onMouseMoved(int x, int y) = 0;
        virtual void onMouseScrolled(
            sf::Mouse::Wheel wheel, float delta,
            int x, int y
        ) = 0;
        virtual void onWindowResized(
            unsigned int width, unsigned int height
        ) = 0;
        virtual void onTextEntered(uint32_t character) = 0;
    };

    typedef std::shared_ptr<IWidget> IWidgetPtr;
}
