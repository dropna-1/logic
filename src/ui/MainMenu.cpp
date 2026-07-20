#include <string>
#include "ui/MainMenu.hpp"
#include <ftxui/component/component.hpp>
#include <ftxui/component/component_options.hpp>
#include <ftxui/dom/elements.hpp>

using namespace ftxui;

MainMenu::MainMenu(std::function<void()> on_play, std::function<void()> on_help,
std::function<void()> on_exit) : on_play_(std::move(on_play)),
 on_exit_(std::move(on_exit)),  on_help_(std::move(on_help))
{
    auto play = Button("Play", on_play_);
    auto help = Button("Help", on_help_);
    auto exit = Button("Exit", on_exit_);

    auto container = ftxui::Container::Vertical({
        play,
        help,
        exit
    });

    component_ = Renderer(container, [=]
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