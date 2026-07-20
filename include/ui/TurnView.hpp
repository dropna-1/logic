#pragma once

#include <ftxui/dom/elements.hpp>
#include <string>

class Player;

class TurnView
{
public:
    ftxui::Element Render(Player& currentPlayer,int turnNumber) const;
};