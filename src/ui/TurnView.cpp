#include "ui/TurnView.hpp"

#include "Player/player.hpp"
#include "Characters/Hero.hpp"
#include "Game/Game.hpp"

using namespace ftxui;

Element TurnView::Render(const Game& game , Player& player) const
{
    auto hero = player.getHero() ;

    return window(
        text(" TURN ") | color(Color::Gold1) | bold,

        vbox({

            hbox({
                text("Remaining Action : ")
                    | color(Color::GrayLight),

                text(std::to_string(game.getRemainingActions()))
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