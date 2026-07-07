#pragma once

#include "Characters/Hero.hpp"
#include "board.hpp"
#include "player.hpp"

class GameContext
{
    public :
    Player* currentPlayer ;
    Player* enemyPlayer;
    Character* attacker;
    Character* defender;
    Board* board;
    std::vector<Character*> getTargets(EffectTarget target);
};