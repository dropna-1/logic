#include "ui/InfoScreen.hpp"

using namespace ftxui;

Element InfoScreen::Render(
    Board& board,
    Player& player1,
    Player& player2, 
    const Game& game 
) const
{
    Element turnPanel = turnView.Render(game,player1) ;
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
        turnPanel ,

        hbox({

            boardPanel | flex | color(Color::White),

            separator(),

            statusPanel | color(Color::BlueViolet)

        }),

        separator(),

        handPanel | color(Color::BlueViolet)

    });
}