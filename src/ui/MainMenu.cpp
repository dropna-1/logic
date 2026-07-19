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

    auto container = ftxui::Container::Vertical({
        play,
        help,
        exit
    });

    component_ = Renderer(container, [play, help, exit]
    {
        return vbox({
            filler(),
            text("╔════════════════════════════════════════════════════════════╗") | center,
            text("║                        UNMATCHED                           ║") | bold | color(Color::Cyan) | center,
            text("╚════════════════════════════════════════════════════════════╝") | center,
            separator() | color(Color::Black) | bold,
            play->Render(),
            help->Render(),
            exit->Render(),
            filler()
        }) | borderRounded | color(Color::BlueViolet) | center;
    });
}

ftxui::Component MainMenu::GetComponent(){
    return component_;
}