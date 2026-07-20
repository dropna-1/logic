#pragma once

#include <ftxui/dom/elements.hpp>

class Player;

class StatusView
{
    public:
        ftxui::Element Render(Player& current,Player& opponent) const;
};