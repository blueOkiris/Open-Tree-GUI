#pragma once

#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>
#include <Widget.hpp>

namespace opentree {
    struct Container : public IWidget {
        virtual std::vector<IWidgetPtr> children() = 0;
        virtual void addChild(IWidgetPtr child) = 0;
        
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
    struct WindowContainer : public Container {
        private:
            std::vector<IWidgetPtr> _children;
            sf::RenderWindow &_window;
        
        public:            
            WindowContainer(sf::RenderWindow &window);
            void setDrawRect(const Rect drawRect) override;
            std::vector<IWidgetPtr> children() override;
            void addChild(IWidgetPtr child) override;
            void draw(
                sf::RenderTarget &target, sf::RenderStates states
            ) const override;
    };

    // Holds its children but with margins
    struct MarginContainer : public Container {
        private:
            std::vector<IWidgetPtr> _children;
            Rect _drawRect, _marginRect;
        
        public:
            static IWidgetPtr create(const AttributeSet &attr);

            MarginContainer(Rect margins);
            void setDrawRect(const Rect drawRect) override;
            std::vector<IWidgetPtr> children() override;
            void addChild(IWidgetPtr child) override;
            void draw(
                sf::RenderTarget &target, sf::RenderStates states
            ) const override;
    };

    // Evenly separates its children horizontally
    struct HBoxContainer : public Container {
        private:
            std::vector<IWidgetPtr> _children;
            Rect _drawRect;
            int _separation;
        
        public:
            static IWidgetPtr create(const AttributeSet &attr);

            HBoxContainer(int separation);
            void setDrawRect(const Rect drawRect) override;
            std::vector<IWidgetPtr> children() override;
            void addChild(IWidgetPtr child) override;
            void draw(
                sf::RenderTarget &target, sf::RenderStates states
            ) const override;
    };

    // Evenly separates its children vertically
    struct VBoxContainer : public Container {
        private:
            std::vector<IWidgetPtr> _children;
            Rect _drawRect;
            int _separation;
        
        public:
            static IWidgetPtr create(const AttributeSet &attr);

            VBoxContainer(int separation);
            void setDrawRect(const Rect drawRect) override;
            std::vector<IWidgetPtr> children() override;
            void addChild(IWidgetPtr child) override;
            void draw(
                sf::RenderTarget &target, sf::RenderStates states
            ) const override;
    };
}
