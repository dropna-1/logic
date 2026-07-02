#pragma once 

#include <vector>
#include <memory>
class Card;

class CardFactory
{
public:

    static std::vector<std::shared_ptr<Card>> createSherlockDeck();
    static std::vector<std::shared_ptr<Card>> createDraculaDeck();
};