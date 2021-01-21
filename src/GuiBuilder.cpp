#include <map>
#include <iostream>
#include <string>
#include <memory>
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

std::shared_ptr<Window> GuiBuilder::fromString(const std::string &src) {
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
        return nullptr;
    }

    if(std::string(doc.FirstChildElement()->Name()) != "window-container") {
        std::cout << "Error: First node is not window-container." << std::endl;
        return nullptr;
    }

    // Get the size stuff
    auto sizeStr = doc.FirstChildElement()->Attribute("size");
    if(sizeStr == NULL) {
        std::cout
            << "Error: No size attribute provided in win cont!"
            << std::endl;
        return nullptr;
    }
    auto sizeNumStrs = strsplit(sizeStr, ',');
    if(sizeNumStrs.size() != 2) {
        std::cout
            << "Error: Wrong number of args in win cont size attr!"
            << std::endl;
        return nullptr;
    }
    unsigned int width = 0, height = 0;
    try {
        width = std::stoi(sizeNumStrs[0]);
        height = std::stoi(sizeNumStrs[1]);
    } catch(...) {
        std::cout << "Error: Failed to parse size in win cont!" << std::endl;
        return nullptr;
    }

    // Get the min size stuff
    sizeStr = doc.FirstChildElement()->Attribute("min-size");
    if(sizeStr == NULL) {
        std::cout
            << "Error: No min-size attribute provided in win cont!"
            << std::endl;
        return nullptr;
    }
    sizeNumStrs = strsplit(sizeStr, ',');
    if(sizeNumStrs.size() != 2) {
        std::cout
            << "Error: Wrong number of args in win cont min-size attr!"
            << std::endl;
        return nullptr;
    }
    unsigned int minWidth = 0, minHeight = 0;
    try {
        minWidth = std::stoi(sizeNumStrs[0]);
        minHeight = std::stoi(sizeNumStrs[1]);
    } catch(...) {
        std::cout
            << "Error: Failed to parse min-size in win cont!"
            << std::endl;
        return nullptr;
    }

    // Get title
    auto titleStr = doc.FirstChildElement()->Attribute("title");
    if(titleStr == NULL) {
        std::cout << "Error: No title attr in window container!" << std::endl;
        return nullptr;
    }

    auto window = std::make_shared<Window>(
        Vector2 { width, height }, Vector2 { minWidth, minHeight },
        std::string(titleStr)
    );

    // Add children things
    auto firstChild = doc.FirstChildElement()->FirstChildElement();
    while(firstChild) {
        //std::cout << "Child: " << firstChild->Name() << std::endl;
        window->addWidget(_fromXmlElement(firstChild));
        firstChild = firstChild->NextSiblingElement();
    }
    
    return window;
}

IWidgetPtr GuiBuilder::_fromXmlElement(tinyxml2::XMLElement *elem) {
    // First construct self from attributes and create func
    AttributeSet attrList;
    auto attr = elem->FirstAttribute();
    while(attr) {
        /*std::cout
            << "Attr: { " << attr->Name() << ", " << attr->Value() << " }"
            << std::endl;*/
        attrList[attr->Name()] = attr->Value();
        attr = attr->Next();
    }
    auto self = _createFuncs[elem->Name()](attrList);

    // Add children
    auto child = elem->FirstChildElement();
    while(child) {
        auto selfAsCont = std::dynamic_pointer_cast<IContainer>(self);

        if(!self) {
            std::cout
                << "Attempting to add child to non container in "
                << elem->Name() << "!"
                << std::endl;
        } else {
            selfAsCont->addChild(_fromXmlElement(child));
        }

        child = child->NextSiblingElement();
    }

    return self;
}
