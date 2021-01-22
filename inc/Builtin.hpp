#pragma once

#include <SFML/Graphics.hpp>
#include <Widget.hpp>
#include <Utility.hpp>

namespace opentree {
    struct ColorRect : public IWidget {
        private:
            Rect _drawRect;
            sf::Color _color;
            
        public:
            static IWidgetPtr create(
                const AttributeSet &attr, const FunctionSet &funcs
            );

            ColorRect(const Color &color);
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
    
    enum class ButtonState {
        Normal, Hovering, Pressed
    };
    
    struct Button : public IWidget {
        private:
            Rect _drawRect;
            sf::Color _baseColor, _hoverColor, _pressedColor;
            sf::Color _baseFontColor, _hoverFontColor, _pressedFontColor;
            sf::Font _font;
            std::string _text;
            CallBackFunc _callBack;
            
            ButtonState _state;
            
        public:
            static IWidgetPtr create(
                const AttributeSet &attr, FunctionSet funcs
            );

            Button(
                const Color &base, const Color &hover, const Color &pressed,
                const Color &baseFontColor, const Color &hoverFontColor,
                const Color &pressedFontColor,
                const sf::Font font, const std::string &text,
                const CallBackFunc &callBack
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
