#include "Characters/Hero.hpp"
#include "Ability/IAbility.hpp"
#include "Cards/Deck.hpp"
#include "Characters/SideKick.hpp"

#include <iostream> 
using namespace std ;

Hero::Hero(const string& name , int hp,
            int movement,
            AttackType attackType,
            HeroType type) :
            Character(name , hp , movement ,attackType) ,herotype(type)  
{
}

HeroType Hero::getHeroType() const
{
    return herotype;
}

std::shared_ptr<Deck> Hero::getDeck()
{
    return deck;
}

std::shared_ptr<IAbility> Hero::getAbility()
{
    return ability;
}

std::vector<std::shared_ptr<SideKick>>& Hero::getSidekicks()
{
    return sidekicks;
}

void Hero::setDeck(std::shared_ptr<Deck> deck)
{
    this->deck = deck;
}

void Hero::setAbility(std::shared_ptr<IAbility> ability)
{
    this->ability = ability;
}

void Hero::addSidekick(std::shared_ptr<SideKick> sidekick)
{
    sidekicks.push_back(sidekick);
}

bool Hero::hasAliveSidekicks() const
{
    for (const auto& sidekick : sidekicks)
    {
        if (sidekick->isAlive())
        {
            return true;
        }
    }
    return false;
}

void Hero::printInfo() const
{
    std::cout << "=========================\n";
    std::cout << "Hero : " << name << '\n';
    std::cout << "HP : " << hp << "/" << maxHp << '\n';
    std::cout << "Movement : " << movement << '\n';

    std::cout << "Attack Type : ";

    if (attackType == AttackType::Melee)
        std::cout << "Melee\n";
    else
        std::cout << "Ranged\n";

    std::cout << "Sidekicks : " << sidekicks.size() << '\n';

    if (ability)
        std::cout << "Ability Loaded\n";
    else
        std::cout << "No Ability\n";

    if (deck)
        std::cout << "Deck Loaded\n";
    else
        std::cout << "No Deck\n";

    std::cout << "=========================\n";
}
            