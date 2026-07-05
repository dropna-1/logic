#pragma once

#include "Characters/Hero.hpp"
#include "board.hpp"

class GameContext
{
    private :
        Hero* currenthero ; 
        Hero* enemyhero ;
        Board* board ;
        Character* currenttarget ;
    public :
        GameContext(Hero* , Hero* , Board*) ;
        Hero* getCurrentHero() const ;
        Hero* getenemyHero() const ;
        Board* getBoard() const ;
        Character* getTarget() const ;
        void setTarget(Character*) ; 

};