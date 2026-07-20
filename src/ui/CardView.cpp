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
                return "[ ATTACK ]" ;
                
            }
            case CardType::Defend :
            {
                return "[ DEFEND ]" ;
            }
            case CardType::Scheme :
            {
                return "[ SCHEME ]" ;
            }
            case CardType::Versalite :
            {
                return "[ VERSALITE ]" ;    
            }
            default :
            {
                return "Unknown" ;
            }
        }
    }
    Color CardTypeColor(CardType type)
    {
        switch(type)
        {
            case CardType::Attack:
                return Color::RedLight;

            case CardType::Defend:
                return Color::BlueLight;

            case CardType::Scheme:
                return Color::YellowLight;

            case CardType::Versalite:
                return Color::MagentaLight;

            default:
                return Color::White;
        }
    }
}

Element CardView::Render(const Card& card) const
{
    auto title = text(ShortenName(card.getName())) | center | bold | color(Color::White) ;
    auto type = text(CardTypeToString(card.getType())) | center | color(CardTypeColor(card.getType()));
    auto value = hbox({text("Value : ") | color(Color::GrayLight) , text(to_string(card.getValue()))}) ;
    auto boost = hbox({text("Boost : ") | color(Color::GrayLight) ,text(std::to_string(card.getBoost()))});
    return window(title , vbox({type ,separator()  , value , boost})) | size(WIDTH ,EQUAL , 18 ) | color(CardTypeColor(card.getType())) ;
}