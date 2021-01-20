#pragma once

#include <vector>
#include <string>
#include <Widget.hpp>
#include <Window.hpp>

namespace opentree {
    class GuiBuilder {
        private:
            std::vector<FromStringFunc> _createFuncs;
        
        public:
            GuiBuilder();
        
            void addBuildFunction(const FromStringFunc &func);
            Window fromString(const std::string &src);
    };
}
