#pragma once 

#include <memory>
#include <vector>

class Card ;

class Deck 
{
    private :
        std::vector<std::shared_ptr<Card>> drawPile;
        std::vector<std::shared_ptr<Card>> hand;
        std::vector<std::shared_ptr<Card>> discardPile; 
    public :
        Deck() = default ;
        void shuffleDeck() ;
        void addcard(std::shared_ptr<Card> card) ;
        bool drawCard();
        void discardCard(int handIndex);
        int getDrawPileSize() const;
        int getHandSize() const;
        int getDiscardPileSize() const;        
        const std::vector<std::shared_ptr<Card>>& getHand() const;
    
};