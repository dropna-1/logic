#pragma once 
#include "GameContext.hpp"

class IConditions 
{
    public :
        virtual bool check(GameContext& context) const = 0 ; 
        virtual ~IConditions() = default ;
};