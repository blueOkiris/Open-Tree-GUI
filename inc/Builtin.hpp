#pragma once

#include <SFML/Graphics.hpp>
#include <Widget.hpp>

namespace opentree {
    struct ColorRect : public IWidget {
        private:
            Rect _drawRect;
            sf::Color _color;
            
        public:
            static IWidgetPtr create(
                const AttributeSet &attr, const FunctionSet &funcs
            );

            ColorRect(
                uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha
            );
            void setDrawRect(const Rect drawRect) override;
            void onKeyPressed(
                sf::Keyboard::Key code,
                bool altPressed, bool ctrlPressed, bool shiftPressed,
                bool systemPressed
            ) override;
            void onKeyReleased(
                sf::Keyboard::Key code,
                bool altPressed, bool ctrlPressed, bool shiftPressed,
                bool systemPressed
            ) override;
            void onMouseButtonPressed(
                sf::Mouse::Button button, int x, int y
            ) override;
            void onMouseButtonReleased(
                sf::Mouse::Button button, int x, int y
            ) override;
            void onMouseMoved(int x, int y) override;
            void onMouseScrolled(
                sf::Mouse::Wheel wheel, float delta,
                int x, int y
            ) override;
            void onWindowResized(
                unsigned int width, unsigned int height
            ) override;
            void onTextEntered(uint32_t character) override;
            void draw(
                sf::RenderTarget &target, sf::RenderStates states
            ) const override;
    };
}
