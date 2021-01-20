#include <vector>
#include <string>
#include <Containers.hpp>
#include <Builtin.hpp>
#include <Widget.hpp>
#include <Window.hpp>
#include <GuiBuilder.hpp>

using namespace opentree;

GuiBuilder::GuiBuilder() {
    // Add all the builtin widget's create functions
    
    addBuildFunction(MarginContainer::create);
    addBuildFunction(VBoxContainer::create);
    addBuildFunction(HBoxContainer::create);
    
    addBuildFunction(ColorRect::create);
}

void GuiBuilder::addBuildFunction(const FromStringFunc &func) {
    _createFuncs.push_back(func);
}

Window GuiBuilder::fromString(const std::string &src) {
    return Window({ 640, 480 }, { 640, 480 }, "Simple Test");
}
