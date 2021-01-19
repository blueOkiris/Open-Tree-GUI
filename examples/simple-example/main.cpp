#include <Window.hpp>
#include <Builtin.hpp>

using namespace opentree;

int main() {
    Window window({ 640, 480 }, { 640, 480 }, "Simple Test");

    auto outer = MarginContainer::create({ 5, 5, 5, 5 });
    auto outerBG = ColorRect::create(0xFF, 0xFF, 0xFF, 0xFF);

    auto vboxContainer = VBoxContainer::create(32);

    auto hboxContainer1 = HBoxContainer::create(64);
    auto innerInnerContainer1 = MarginContainer::create({ 10, 10, 0, 10 });
    auto innerInnerBG1 = ColorRect::create(0x00, 0x10, 0xFF, 0xFF);
    auto innerInnerContainer2 = MarginContainer::create({ 0, 32, 32, 32 });
    auto innerInnerBG2 = ColorRect::create(0x00, 0x20, 0x30, 0xFF);

    auto hboxContainer2 = HBoxContainer::create(64);
    auto innerInnerContainer3 = MarginContainer::create({ 10, 10, 0, 10 });
    auto innerInnerBG3 = ColorRect::create(0xFF, 0x10, 0xFF, 0xFF);
    auto innerInnerContainer4 = MarginContainer::create({ 0, 32, 32, 32 });
    auto innerInnerBG4 = ColorRect::create(0xE0, 0x20, 0x30, 0xFF);

    innerInnerContainer1->addChild(innerInnerBG1);
    innerInnerContainer2->addChild(innerInnerBG2);
    hboxContainer1->addChild(innerInnerContainer1);
    hboxContainer1->addChild(innerInnerContainer2);

    innerInnerContainer3->addChild(innerInnerBG3);
    innerInnerContainer4->addChild(innerInnerBG4);
    hboxContainer2->addChild(innerInnerContainer3);
    hboxContainer2->addChild(innerInnerContainer4);

    vboxContainer->addChild(hboxContainer1);
    vboxContainer->addChild(hboxContainer2);

    outer->addChild(outerBG);
    outer->addChild(vboxContainer);
    window.addWidget(outer);

    window.run();
}
