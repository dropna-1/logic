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

Color CharacterColor(const string& name)
{
    if(name == "Sherlock")
        return Color::BlueLight;

    if(name == "Dr.Watson")
        return Color::DeepSkyBlue4Bis;

    if(name == "Dracula")
        return Color::RedLight;

    if(name.find("Sister") != string::npos)
        return Color::HotPink;

    return Color::White;
}

Element RenderCharacter(
    const string& name,
    int hp,
    int maxHp
)
{
    Decorator hpColor = color(Color::GreenLight);

    double ratio = static_cast<double>(hp) / maxHp;

    if(ratio <= 0.30)
        hpColor = color(Color::RedLight);
    else if(ratio <= 0.70)
        hpColor = color(Color::YellowLight);

    auto title =
        text(name)
        | color(CharacterColor(name));

    if(name == "Sherlock" ||
       name == "Dracula")
        title = title | bold;

    return hbox({
        title,
        text(" "),
        text(MakeBar(hp,maxHp)) | Decorator(hpColor),
        filler(),
        text(to_string(hp)+"/"+to_string(maxHp)) | Decorator(hpColor)
    });
}



Element RenderPlayer(Player& player )
{
    Element playerInfo =
    vbox({
        text(player.getName())
            | bold
            | color(Color::YellowLight)
            | center,

        text("Age : " + to_string(player.getAge()))
            | color(Color::GrayLight)
            | center,

        separator()
    });

    auto hero = player.getHero() ;
    Elements elements ;
    elements.push_back(playerInfo);
    elements.push_back(separator()) ;
    elements.push_back(RenderCharacter(hero->getname(),hero->getHp(),hero->getMaxhp() )) ;
    for(auto& sidekick : hero->getSidekicks())
    {
        elements.push_back(separatorEmpty()) ;
        elements.push_back(RenderCharacter(sidekick->getname(),sidekick->getHp(),sidekick->getMaxhp() )) ;
    }
    elements.push_back(separator());
    elements.push_back(hbox({text("Hand") | bold | color(Color::White) ,filler() ,
        text(std::to_string(hero->getDeck()->getHand().size())) | color(Color::White) })) ;
    elements.push_back(separatorEmpty()) ;
    elements.push_back(hbox({text("Discard") | bold | color(Color::White) ,filler()  , 
        text(std::to_string(hero->getDeck()->getDiscardPileSize())) | color(Color::White) })
    );
    
    return window(text(player.getName()) | color(CharacterColor(player.getHero()->getname())) | bold | center , 
                  vbox(move(elements))
                  ) | size(WIDTH, EQUAL , 34) ;
}

Element StatusView::Render(Player& currentplayer,Player& enemyPLayer) const
{
    return hbox({RenderPlayer(currentplayer) ,
                separator() , 
                RenderPlayer(enemyPLayer) }) ;
}



