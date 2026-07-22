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
    Color bg;
    Color border;

    switch(card.getType())
    {
        case CardType::Attack:
            bg = Color::DarkRedBis;
            border = Color::RedLight;
            break;

        case CardType::Defend:
            bg = Color::DarkBlue ;
            border = Color::BlueLight;
            break;

        case CardType::Scheme:
            bg = Color::DarkGreen;
            border = Color::YellowLight;
            break;

        case CardType::Versalite:
            bg = Color::Purple4;
            border = Color::MagentaLight;
            break;

        default:
            bg = Color::Black;
            border = Color::White;
    }

    auto title =
        text(ShortenName(card.getName()))
        | center
        | bold
        | color(Color::White);

    auto type =
        text(CardTypeToString(card.getType()))
        | center
        | bold
        | color(Color::White);

    auto value =
        hbox({
            text("Value : ") | color(Color::GrayLight),
            text(to_string(card.getValue()))
                | bold
                | color(Color::White)
        });

    auto boost =
        hbox({
            text("Boost : ") | color(Color::GrayLight),
            text(to_string(card.getBoost()))
                | color(Color::White)
        });

    auto fighter = 
        hbox({
            text("Fighter : ") | color(Color::GrayLight) ,
            text(card.getFighterName()) | color(Color::White)
        });

    auto content =
        vbox({
            type,
            separator(),
            value,
            boost,
            fighter
        })
        | bgcolor(bg);

    return window(title, content)
           | size(WIDTH, EQUAL, 18)
           | color(border);
}