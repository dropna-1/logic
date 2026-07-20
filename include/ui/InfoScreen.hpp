#pragma once

#include <ftxui/dom/elements.hpp>

class Game;

class InfoScreen
{
public:

    ftxui::Element Render(Game& game) const;

};