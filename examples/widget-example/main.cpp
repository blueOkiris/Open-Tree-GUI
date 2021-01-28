#include <fstream>
#include <iostream>
#include <Widget.hpp>
#include <GuiBuilder.hpp>

int main() {
    auto fileName = "examples/widget-example/layout.xml";
    std::string layout;
    try {
        std::ifstream layoutFile;
        layoutFile.open(fileName);
        if(layoutFile.fail()) {
            std::cout << "Failed to read file!" << std::endl;
            return -1;
        }

        layoutFile.seekg(0, std::ios::end);
        auto size = layoutFile.tellg();
        std::string str((unsigned) size, ' ');
        layoutFile.seekg(0);
        layoutFile.read(&str[0], size);
        
        layout = str;
    } catch(...) {
        std::cout << "Failed to read file!" << std::endl;
        return -1;
    }
    
    opentree::GuiBuilder builder;
    builder.addCallBackFunction(
        "btn-func", [] (opentree::IWidgetPtr) {
            std::cout << "Hello, world!" << std::endl;
        }
    );
    auto window = builder.fromString(layout);
    if(window) {
        window->run();
    }

    return 0;
}
