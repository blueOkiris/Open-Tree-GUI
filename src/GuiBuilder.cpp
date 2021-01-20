#include <GuiBuilder.hpp>

using namespace opentree;

void GuiBuilder::addBuildFunction(const FromStringFunc &func) {
    _createFuncs.push_back(func);
}

Window GuiBuilder::fromString(const std::string &src) {
    return Window({ 640, 480 }, { 640, 480 }, "Simple Test");
}
