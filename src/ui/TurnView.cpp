#include "ui/TurnView.hpp"

#include "Player/player.hpp"
#include "Characters/Hero.hpp"

using namespace ftxui;

Element TurnView::Render(Player& player, int turn) const
{
    auto hero = player.getHero();

    return window(
        text(" TURN ") | color(Color::Gold1) | bold,

        vbox({

            hbox({
                text("Turn ")
                    | color(Color::GrayLight),

                text(std::to_string(turn))
                    | color(Color::Gold1)
                    | bold,
            }),

            separator(),

            hbox({
                filler(),

                text(hero->getname())
                    | color(Color::BlueLight)
                    | bold,

                text("'s Turn")
                    | color(Color::White),

                filler()
            })

        })
    )
    | color(Color::DarkGoldenrod);
}