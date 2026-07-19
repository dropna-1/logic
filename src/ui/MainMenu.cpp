#include <vector>
#include <string>
#include "ui/MainMenu.hpp"

#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>

using namespace ftxui;

int MainMenu::show(){
    auto screen = ScreenInteractive::TerminalOutput();

    std::vector<std::string> options{"Play", "Help", "Exit"};
    int selected = 0;

    auto menu = Menu(&options, &selected);
    auto renderer = Renderer(menu, [&]{return menu->Render();});

    screen.Loop(renderer);
    return selected;

}