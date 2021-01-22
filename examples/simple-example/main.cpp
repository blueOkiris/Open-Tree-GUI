#include <memory>
#include <Window.hpp>
#include <Builtin.hpp>

using namespace opentree;

/*
 * Note, the proper way to do things is using the GUI Builder.
 * This example serves to illustrate how to GuiBuilder class functions
 * under the hood more or less
 * 
 * It constructs pointers to data and appends children and things without
 * building from text
 */
int main() {
    Window window({ 640, 480 }, { 640, 480 }, "Simple Test");
    auto callBacks = FunctionSet();

    auto outer = std::dynamic_pointer_cast<MarginContainer>(
        MarginContainer::create({ { "margin", "5,5,5,5"} }, callBacks)
    );
    auto outerBG = ColorRect::create({ { "color", "#FFFFFFFF" } }, callBacks);

    auto vboxContainer = std::dynamic_pointer_cast<VBoxContainer>(
        VBoxContainer::create({ { "separation", "32" } }, callBacks)
    );

    auto hboxContainer1 = std::dynamic_pointer_cast<HBoxContainer>(
        HBoxContainer::create({ { "separation", "64" } }, callBacks)
    );
    auto innerInnerContainer1 = std::dynamic_pointer_cast<MarginContainer>(
        MarginContainer::create({ { "margin", "10,10,0,10" } }, callBacks)
    );
    auto innerInnerBG1 = ColorRect::create(
        { { "color", "#0010FFFF" } }, callBacks
    );
    auto innerInnerContainer2 = std::dynamic_pointer_cast<MarginContainer>(
        MarginContainer::create({ { "margin", "0,32,32,32" } }, callBacks)
    );
    auto innerInnerBG2 = ColorRect::create(
        { { "color", "#002030FF" } }, callBacks
    );

    auto hboxContainer2 = std::dynamic_pointer_cast<HBoxContainer>(
        HBoxContainer::create({ { "separation", "64" } }, callBacks)
    );
    auto innerInnerContainer3 = std::dynamic_pointer_cast<MarginContainer>(
        MarginContainer::create({ { "margin", "10,10,0,10" } }, callBacks)
    );
    auto innerInnerBG3 = ColorRect::create(
        { { "color", "#FF10FFFF" } }, callBacks
    );
    auto innerInnerContainer4 = std::dynamic_pointer_cast<MarginContainer>(
        MarginContainer::create({ { "margin", "0,32,32,32" } }, callBacks)
    );
    auto innerInnerBG4 = ColorRect::create(
        { { "color", "#E02030FF" } }, callBacks
    );

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
