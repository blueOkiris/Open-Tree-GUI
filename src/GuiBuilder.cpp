#include <map>
#include <iostream>
#include <string>
#include <TinyXml2.hpp>
#include <Containers.hpp>
#include <Builtin.hpp>
#include <Widget.hpp>
#include <Window.hpp>
#include <Utility.hpp>
#include <GuiBuilder.hpp>

using namespace opentree;

GuiBuilder::GuiBuilder() {
    // Add all the builtin widget's create functions
    
    addBuildFunction("margin-container", MarginContainer::create);
    addBuildFunction("vbox-container", VBoxContainer::create);
    addBuildFunction("hbox-container", HBoxContainer::create);
    
    addBuildFunction("color-rect", ColorRect::create);
}

void GuiBuilder::addBuildFunction(
        const std::string &tagName, const FromStringFunc &func) {
    _createFuncs[tagName] = func;
}

Window GuiBuilder::fromString(const std::string &src) {
    tinyxml2::XMLDocument doc(true, tinyxml2::COLLAPSE_WHITESPACE);
    auto errorCode = doc.Parse(src.c_str(), src.length());

    // Test
    /*if(errorCode == tinyxml2::XMLError::XML_SUCCESS) {
        auto text = doc.FirstChildElement("window")->GetText();
        std::cout << "Window with text: " << text << std::endl;
    } else {
        std::cout << "Error: " << errorCode << std::endl;
    }*/

    if(errorCode != tinyxml2::XMLError::XML_SUCCESS) {
        std::cout
            << "An error occurred parsing xml. Error code: "
            << errorCode << "." << std::endl
            << "Message: " << doc.ErrorStr() << "." << std::endl;
        return Window({ 640, 480 }, { 640, 480 }, "EMPTY");
    }

    if(std::string(doc.FirstChildElement()->Name()) != "window-container") {
        std::cout << "Error: First node is not window-container." << std::endl;
        return Window({ 640, 480 }, { 640, 480 }, "EMPTY");
    }

    // Get the size stuff
    auto sizeStr = doc.FirstChildElement()->Attribute("size");
    if(sizeStr == NULL) {
        std::cout
            << "Error: No size attribute provided in win cont!"
            << std::endl;
        return Window({ 640, 480 }, { 640, 480 }, "EMPTY");
    }
    auto sizeNumStrs = strsplit(sizeStr, ',');
    if(sizeNumStrs.size() != 2) {
        std::cout
            << "Error: Wrong number of args in win cont size attr!"
            << std::endl;
        return Window({ 640, 480 }, { 640, 480 }, "EMPTY");
    }
    unsigned int width = 0, height = 0;
    try {
        width = std::stoi(sizeNumStrs[0]);
        height = std::stoi(sizeNumStrs[1]);
    } catch(...) {
        std::cout << "Error: Failed to parse size in win cont!" << std::endl;
        return Window({ 640, 480 }, { 640, 480 }, "EMPTY");
    }

    // Get the min size stuff
    sizeStr = doc.FirstChildElement()->Attribute("min-size");
    if(sizeStr == NULL) {
        std::cout
            << "Error: No min-size attribute provided in win cont!"
            << std::endl;
        return Window({ 640, 480 }, { 640, 480 }, "EMPTY");
    }
    sizeNumStrs = strsplit(sizeStr, ',');
    if(sizeNumStrs.size() != 2) {
        std::cout
            << "Error: Wrong number of args in win cont min-size attr!"
            << std::endl;
        return Window({ 640, 480 }, { 640, 480 }, "EMPTY");
    }
    unsigned int minWidth = 0, minHeight = 0;
    try {
        minWidth = std::stoi(sizeNumStrs[0]);
        minHeight = std::stoi(sizeNumStrs[1]);
    } catch(...) {
        std::cout
            << "Error: Failed to parse min-size in win cont!"
            << std::endl;
        return Window({ 640, 480 }, { 640, 480 }, "EMPTY");
    }

    // Get title
    auto titleStr = doc.FirstChildElement()->Attribute("title");
    if(titleStr == NULL) {
        std::cout << "Error: No title attr in window container!" << std::endl;
        return Window({ 640, 480 }, { 640, 480 }, "EMPTY");
    }
    
    return Window(
        { width, height }, { minWidth, minHeight }, std::string(titleStr)
    );
}

IWidgetPtr _fromXmlElement(tinyxml2::XMLElement *elem) {
    return nullptr;
}
