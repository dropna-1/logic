#include "ui/StatusView.hpp"
#include "Player/player.hpp"
#include "Characters/Hero.hpp"
#include "Characters/SideKick.hpp"
#include "Cards/Deck.hpp"
#include "ftxui/dom/elements.hpp"

#include <string>
using namespace ftxui ;
using namespace std ;

string MakeBar(int hp , int maxhp , int width = 10)
{
    if(maxhp < 0)
    {
        return "DEAD" ;
    }
    int filled = hp*width/ maxhp;
    string result = "[" ;
    for(int i = 0 ; i < width ; i++)
    {
        if(i < filled)
        {
            result += '#' ;
        }
        else
        {
            result += '-' ;
        }
    }
    result += ']' ;
    return result ;
}

static string ShortName(const std::string& name)
{
    if (name == "Sherlock")
        return "SH";

    if (name == "Dr.Watson")
        return "WA";

    if (name == "Dracula")
        return "DR";

    if (name == "Sister 1")
        return "S1";

    if (name == "Sister 2")
        return "S2";

    if (name == "Sister 3")
        return "S3";

    return name;
}

Element RenderCharacter(const string& name, int hp, int maxHp)
{
    return vbox({
        hbox({text(ShortName(name)), text(" ")  ,text(MakeBar(hp, maxHp)) ,filler() , text(to_string(hp) + "/" + to_string(maxHp))})  
    }) ;
}

Element RenderPlayer(Player& player)
{
    auto hero = player.getHero() ;
    Elements elements ;
    elements.push_back(RenderCharacter(hero->getname(),hero->getHp(),hero->getMaxhp())) ;
    for(auto& sidekick : hero->getSidekicks())
    {
        elements.push_back(separatorEmpty()) ;
        elements.push_back(RenderCharacter(sidekick->getname(),sidekick->getHp(),sidekick->getMaxhp())) ;
    }
    elements.push_back(separator());
    elements.push_back(hbox({text("Hand"),filler(),
        text(std::to_string(hero->getDeck()->getHand().size()))})) ;
    elements.push_back(hbox({text("Discard"),filler(),
        text(std::to_string(hero->getDeck()->getDiscardPileSize()))})
    );
    
    return window(text(hero->getname()) | bold | center, 
                  vbox(move(elements))
                  ) | size(WIDTH, EQUAL , 34) ;
}

Element StatusView::Render(Player& currentplayer,Player& enemyPLayer) const
{
    return hbox({RenderPlayer(currentplayer) ,
                separator() , 
                RenderPlayer(enemyPLayer) }) ;
}



