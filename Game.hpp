#pragma once
#include <iostream>
#include <vector>
#include "board.hpp"
#include "include/Characters/Hero.hpp"
#include "Factory/HeroFactory.hpp"
#include "Cards/Cards.hpp"
#include "player.hpp"
using namespace std;

struct AttackOption {
    Character* attacker;
    Character* target;
};

class Game {

    Board board;

    Player player1;
    Player player2;
    
    shared_ptr<Hero> dracula;
    shared_ptr<Hero> sherlock;

    Player* currentPlayer;
    Player* otherPlayer;

    int actionsRemaining = 2;

public:

    Game();
    void setupGame();
    void startTurn();
    void changeTurn();
    Hero* checkWinner();
    Board& getBoard();
    /*-----------------------------------------------------------------*/
    void setPlayer1(const string& name, const int& age);
    void setPlayer2(const string& name, const int& age);
    Player* getCurrentPlayer();
    Player* getFirstPlayer();
    void choiceHero(Player& player, HeroType choice);
    vector<int> getSidekickPlacement();
    /*-----------------------------------------------------------------*/
    vector<int> getAvailableMoves(Character* character, const int& move);
    bool canMove(int to, const vector<int>& reachable);
    void move(Character* character, const int& pos);
    int boost(Character* self, vector<int>& cards);
    /*------------------------------------------------------------------*/
    bool useAction();
    int getRemainingActions() const;
    /*------------------------------------------------------------------*/
    vector<AttackOption>& getAttackableTargets();
    vector<Card*> getPlayableAttackCard(Character* attacker);
    vector<Card*> getPlayableDefenseCard(Character* defender);
    /*------------------------------------------------------------------*/
    void playScheme(Character* source, const int& schemeCardIndex);
    /*------------------------------------------------------------------*/
    int calculateDamage(Card* attack, Card* defense);
    void combat(AttackOption option, const int& attackCardIndex, 
        const int& defenseCardIndex);
};