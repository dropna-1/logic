#pragma once

#include <ftxui/dom/elements.hpp>

#include "Board/board.hpp"
#include "Player/player.hpp"

#include "ui/BoardView.hpp"
#include "ui/StatusView.hpp"
#include "ui/HandView.hpp"
#include "ui/TurnView.hpp"

class InfoScreen
{
public:

    ftxui::Element Render(
        Board& board,
        Player& player1,
        Player& player2
    ) const;

private:
    TurnView turnView ;
    BoardView boardView;
    StatusView statusView;
    HandView handView;
};