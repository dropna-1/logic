#include "ui/HelpScreen.hpp"

#include <ftxui/component/component.hpp>
#include <ftxui/component/event.hpp>
#include <ftxui/dom/elements.hpp>

using namespace ftxui;

HelpScreen::HelpScreen(std::function<void()> on_back)
    : on_back_(std::move(on_back))
{
    auto back = Button("Back", on_back_);
    auto container = Container::Vertical({back});
    component_ = CatchEvent(
        Renderer(container, [=](){
            return vbox({
                text("UNMATCHED - HELP")
                    | bold
                    | center
                    | color(Color::Cyan),
                separator(),

                text("Goal:"),

                text("  Defeat the enemy Hero."),

                separator(),

                text("Each turn you have 2 actions."),

                separator(),

                text("Available actions:"),
                text("  • Maneuver"),
                text("  • Attack"),
                text("  • Scheme"),

                separator(),

                text("Maneuver"),
                text("  Draw one card."),
                text("  Move one character."),

                separator(),

                text("Attack"),
                text("  Choose attacker."),
                text("  Choose target."),
                text("  Both players play combat cards."),

                separator(),

                text("Scheme"),
                text("  Play a Scheme card."),
                text("  Follow the card effect."),

                separator(),

                text("Win Condition"),
                text("  Reduce the enemy Hero's HP to 0."),

                separator(),

                text("Press ESC or Select Back to return")
                    | center
                    | color(Color::Yellow),
                
                back->Render() | size(WIDTH, EQUAL, 70) | color(Color::Cyan)
            })
            | borderRounded
            | size(WIDTH, EQUAL, 70)
            | center;
        }),
        [this](ftxui::Event event) {
            if (event == Event::Escape) {
                if (on_back_)
                    on_back_();
                return true;
            }
            return false;
        }
    );
}

ftxui::Component HelpScreen::GetComponent() {
    return component_;
}