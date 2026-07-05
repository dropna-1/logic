#include "Effects/GameContext.hpp"

GameContext::GameContext(Hero* currentHero , Hero* enemyHero , Board* Board) : 
    currenthero(currentHero) , 
    enemyhero(enemyHero) , 
    board(Board) 
{
}

Hero* GameContext::getCurrentHero() const
{
    return currenthero ;
}

Hero* GameContext::getenemyHero() const 
{
    return enemyhero ;
}

Board* GameContext::getBoard() const
{
    return board ;
}

Character* GameContext::getTarget() const
{
    return currenttarget ;
}

void GameContext::setTarget(Character* target)
{
    currenttarget = target;
}