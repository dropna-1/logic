#include "ui/CardView.hpp"
#include "Cards/Cards.hpp"
#include "ftxui/dom/elements.hpp"

#include <algorithm>
#include <string>
using namespace ftxui ;
using namespace std ;

namespace 
{
    string ShortenName(const string& name , size_t maxlength = 18)
    {
        if(name.length() <= maxlength)
        {
            return name ;
        }   
        return name.substr(0 , maxlength - 3) + "..." ;
    }

    string CardTypeToString(CardType type)
    {
        switch(type) 
        {
            case CardType::Attack :
            {
                return "Type : Attack" ;
            }
            case CardType::Defend :
            {
                return "Type : Defend" ;
            }
            case CardType::Scheme :
            {
                return "Type : Scheme" ;
            }
            case CardType::Versalite :
            {
                return "Type : Versalite" ;    
            }
            default :
            {
                return "Unknown" ;
            }
        }
    }
}

Element CardView::Render(const Card& card) const
{
    auto title = text(ShortenName(card.getName())) | center | bold  ;
    auto type = text(CardTypeToString(card.getType())) | center ;
    auto value = hbox({text("Value : ") , text(to_string(card.getValue()))}) ;
    auto boost = hbox({text("Boost : "),text(std::to_string(card.getBoost()))});
    return window(title , vbox({type ,separator()  , value , boost})) | size(WIDTH ,EQUAL , 18 ) ;
}