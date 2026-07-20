#include "ui/HandView.hpp"
#include "ui/CardView.hpp"
#include "Cards/Cards.hpp"
#include "Player/player.hpp"
#include "Cards/Deck.hpp"
#include "ftxui/dom/elements.hpp"
using namespace ftxui ;
using namespace std ;

Element HandView::Render(Player& player) const
{
    CardView cardview ;
    Elements cards ;
    for(auto& card : player.getHero()->getDeck()->getHand())
    {
        cards.push_back(cardview.Render(*card)) ;
        //cards.push_back(separatorEmpty()) ;
    }
    /*if (!cards.empty())
    {
        cards.pop_back();
    }*/
    std::string title = "Hand (" +to_string(player.getHero()->getDeck()->getHand().size()) +"/7)";
    return window(text(title) | bold | center,hbox(std::move(cards)));
}