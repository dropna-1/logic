#pragma once

#include <ftxui/dom/elements.hpp>
#include <string>

class Player;
class Game ;

class TurnView
{
public:
    ftxui::Element Render(const Game& game , Player& player) const;
};