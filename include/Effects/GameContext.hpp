#pragma once

#include "Characters/Hero.hpp"
#include "Characters/SideKick.hpp"
#include "board.hpp"
#include "player.hpp"

class GameContext
{
    private :
        Player* currentPlayer ;
        Player* enemyPlayer;
        Character* attacker;
        Character* defender;
        Board* board;
    public :
        GameContext(Player* , Player*, Character* , Character* , Board* );
        Player* getCurrentPlayer() const ;
        Player* getEnemyPlayer() const ;
        Character* getAttacker() const ;
        Character* getDefender() const ; 
        Board* getBoard() const ;
        std::vector<Character*> getTargets(EffectTarget target);
        std::vector<Character*> resolve(ConditionTarget target) const;
};