#pragma once

#include <iostream>
#include "Cards/Cards.hpp"
#include "Effects/GameContext.hpp"

class IAbility
{
    public:
        virtual ~IAbility() = default;
        
        virtual bool allowCancel(Card* card , GameContext& context) 
        {
            return true ;
        }
        virtual void execute(Character*) ;
        virtual std::string getName() const = 0;
        virtual std::string getDescription() const = 0;
};