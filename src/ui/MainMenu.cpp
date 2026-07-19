#include <vector>
#include <string>
#include "ui/MainMenu.hpp"

#include <ftxui/component/component.hpp>
#include <ftxui/component/component_options.hpp>
#include <ftxui/dom/elements.hpp>

using namespace ftxui;

MainMenu::MainMenu(std::function<void()> on_play) : on_play_(std::move(on_play))
{
    auto play = Button("Play", on_play_);
    auto help = Button("Help", [] {});
    auto exit = Button("Exit", [] {});

    auto container = Container::Vertical({
        play,
        help,
        exit
    });

    component_ = Renderer(container, [&]
    {
        return vbox({
            filler(),
            text("UnMatched") | bold | center,
            separator(),
            play->Render(),
            help->Render(),
            exit->Render(),
            filler()
        });
    });
}

ftxui::Component MainMenu::GetComponent(){
    return component_;
}