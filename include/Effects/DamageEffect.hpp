#pragma once

#include "IEffects.hpp"

class DamageEffect : public IEffect
{
    private :
        int damage ;
    public :
        DamageEffect(int damage) ;
        int getdamage() ;
        void execute(GameContext& context) override ;
};