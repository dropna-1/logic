#include "Ability/DraculaAbility.hpp"
#include "Cards/Deck.hpp"
// inam esm o tozihatesho badan misazam
std::string DraculaAbility::getName() const
{
    return "Draculaaaaa";
}

std::string DraculaAbility::getDescription() const
{
    return "dadadadraaacilaalal";
}

void DraculaAbility::execute(Character* target , Hero* hero)
{
    target->takeDamage(1) ;
    hero->getDeck()->drawCard() ;
}

void DraculaAbility::SendRequest(Game* game)
{
    game->requestAction(make_unique<DraculaAction>()) ;
}