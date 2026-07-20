#pragma once 

#include <ftxui/dom/elements.hpp>

class Card ;

class CardView 
{
    public :
        ftxui::Element Render(const Card& card) const ;
};