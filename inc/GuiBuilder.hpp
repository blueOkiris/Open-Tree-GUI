#pragma once

#include <map>
#include <string>
#include <TinyXml2.hpp>
#include <Widget.hpp>
#include <Window.hpp>

namespace opentree {
    class GuiBuilder {
        private:
            static IWidgetPtr _fromXmlElement(tinyxml2::XMLElement *elem);

            std::map<std::string, FromStringFunc> _createFuncs;
        
        public:
            GuiBuilder();
        
            void addBuildFunction(
                const std::string &tagName,
                const FromStringFunc &func
            );
            Window fromString(const std::string &src);
    };
}
