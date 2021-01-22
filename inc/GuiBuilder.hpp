#pragma once

#include <map>
#include <string>
#include <memory>
#include <TinyXml2.hpp>
#include <Widget.hpp>
#include <Window.hpp>

namespace opentree {    
    class GuiBuilder {
        private:
            std::map<std::string, FromStringFunc> _createFuncs;
            FunctionSet _callBacks;
            IWidgetPtr _fromXmlElement(tinyxml2::XMLElement *elem);
        
        public:
            GuiBuilder();
            
            void addCallBackFunction(
                const std::string &funcName,
                const CallBackFunc &func
            );
            void addBuildFunction(
                const std::string &tagName,
                const FromStringFunc &func
            );
            std::shared_ptr<Window> fromString(const std::string &src);
    };
}
