#pragma once

#include "Characters/Hero.hpp"
#include "Characters/SideKick.hpp"
#include "board.hpp"
#include "player.hpp"
#include "Cards/Cards.hpp"
#include "Game.hpp"
class Card ;

class GameContext
{
    private :
        Player* currentPlayer ;
        Player* enemyPlayer;
        Character* attacker;
        Character* defender;
        Board* board;
        Character* Winner ;
        Card* attackerCard ;
        Card* defenderCard ;
        Game* game ;
    public :
        GameContext(Player* , Player*, Character* , Character* , Board* , Card* ,Card* , Game*);
        Player* getCurrentPlayer() const ;
        Player* getEnemyPlayer() const ;
        Character* getAttacker() const ;
        Character* getDefender() const ; 
        Board* getBoard() const ;
        Card* getAttackerCard() const ;
        Card* getDefenderCard() const ;
        std::vector<Character*> getTargets(EffectTarget target);
        void setWinner(Character*) ;
        Character* getWinner() const ;
        std::vector<Character*> resolve(ConditionTarget target) const;
        Game* getGame() const ;
};