#pragma once

#include <iostream>
#include "Cards/Cards.hpp"
#include "Characters/Character.hpp"

class Game;
class GameContext;
class Card;
class Hero;

class IAbility
{
    public:
        virtual ~IAbility() = default;
        virtual bool allowCancel(Card* card , GameContext& context) 
        {
            return true ;
        }

        virtual bool HasAbilityOnStart() = 0;
        virtual void SendRequest(Game*) 
        {
        }
        virtual void execute(Character* , Hero*) 
        {
        }
        virtual std::string getName() const = 0;
        virtual std::string getDescription() const = 0;
};