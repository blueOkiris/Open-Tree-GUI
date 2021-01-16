#pragma once

#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>
#include <Widget.hpp>

namespace opentree {
    struct Container : public IWidget {
        virtual std::vector<std::shared_ptr<IWidget>> getChildren() = 0;
        
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
    };
    
    // Simply holds its children. Used as the base widget for Window
    struct BasicContainer : public Container {
        private:
            std::shared_ptr<IWidget> _parent;
            std::vector<std::shared_ptr<IWidget>> _children;
            sf::RenderWindow &_window;
        
        public:
            BasicContainer(
                const std::shared_ptr<IWidget> &parent, sf::RenderWindow &window
            );
            std::shared_ptr<IWidget> getParent() override;
            Rect getDrawRect() override;
            std::vector<std::shared_ptr<IWidget>> getChildren() override;
            void draw(
                sf::RenderTarget &target, sf::RenderStates states
            ) const override;
    };
}
