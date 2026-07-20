#include "ui/InfoScreen.hpp"

using namespace ftxui;

Element InfoScreen::Render(
    Board& board,
    Player& player1,
    Player& player2
) const
{
    Element boardPanel =
        boardView.Render(
            board,
            player1,
            player2
        );

    Element statusPanel =
        statusView.Render(
            player1,
            player2
        );

    Element handPanel =
        handView.Render(
            player1
        );

    return vbox({

        hbox({

            boardPanel | flex,

            separator(),

            statusPanel

        }),

        separator(),

        handPanel

    });
}