#include "ui/InfoScreen.hpp"

#include "ui/BoardView.hpp"
#include "ui/StatusView.hpp"
#include "ui/HandView.hpp"

#include "Game/Game.hpp"

using namespace ftxui;

Element InfoScreen::Render(Game& game) const
{
    BoardView board;
    StatusView status;
    HandView hand;

    auto left =
        board.Render(
            game.getBoard(),
            *game.getCurrentPlayer(),
            *game.getOtherPlayer()) |  xflex_shrink ;
    auto right =
        status.Render(
            *game.getCurrentPlayer(),
            *game.getOtherPlayer());
    auto bottom =
        hand.Render(
            *game.getCurrentPlayer());
    return vbox({
        hbox({
            left ,
            separator(),
            right
        }),
        separator(),
        bottom
    });
}