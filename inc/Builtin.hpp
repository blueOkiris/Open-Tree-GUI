#pragma once

#include <SFML/Graphics.hpp>
#include <Widget.hpp>

namespace opentree {
    struct NonContainer : public IWidget {
        Rect drawRect() override;
    };
    
    struct ColorRect : public NonContainer {
        private:
            std::shared_ptr<IWidget> _parent;
            sf::Color _color;
            
        public:
            ColorRect(
                const std::shared_ptr<IWidget> &parent,
                uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha
            );
            
            std::shared_ptr<IWidget> parent() override;
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
