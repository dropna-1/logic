#pragma once 

#include "ftxui/dom/elements.hpp"

class Player ;

class HandView
{
    public :
        ftxui::Element Render(Player& player) const ;
};