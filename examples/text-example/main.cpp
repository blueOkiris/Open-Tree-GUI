#include <GuiBuilder.hpp>

int main() {
    opentree::GuiBuilder builder;
    auto win = builder.fromString(
        "<window-container\n"
        "       size='640,480' min-size='640,480' title='Text Example'>\n"
        "   <margin-container margin='5,5,5,5'>\n"
        "       <color-rect color='#FFFFFFFF'></color-rect>\n"
        "       <vbox-container separation='32'>\n"
        "           <hbox-container separation='64'>\n"
        "               <margin-container margin='10,10,0,10'>\n"
        "                   <color-rect color='#0010FFFF'></color-rect>\n"
        "               </margin-container>\n"
        "               <margin-container margin='0,32,32,32'>\n"
        "                   <color-rect color='#002030FF'></color-rect>\n"
        "               </margin-container>\n"
        "           </hbox-container>\n"
        "           <hbox-container separation='64'>\n"
        "               <margin-container margin='10,10,0,10'>\n"
        "                   <color-rect color='#FF10FFFF'></color-rect>\n"
        "               </margin-container>\n"
        "               <margin-container margin='0,32,32,32'>\n"
        "                   <color-rect color='#E02030FF'></color-rect>\n"
        "               </margin-container>\n"
        "           </hbox-container>\n"
        "       </vbox-container>\n"
        "   </margin-container>\n"
        "</window-container>"
    );
    win.run();

    return 0;
}