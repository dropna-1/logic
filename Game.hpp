#pragma once
#include <iostream>
#include <vector>
#include "board.hpp"
#include "include/Characters/Hero.hpp"
#include "Factory/HeroFactory.hpp"
#include "Cards/Cards.hpp"
#include "player.hpp"
using namespace std;

class Game {

    Board board;

    Player player1;
    Player player2;
    
    shared_ptr<Hero> dracula;
    shared_ptr<Hero> sherlock;

    Hero* self;
    Hero* enemy;

    int actionsRemaining = 2;

public:

    Game();
    vector<int> getAvailableMoves(const int& move);
    bool canMove(int to, const vector<int>& reachable);
    vector<int> free_spaces_for_Sidekicks();
    void changeTurn();
    void startGame();
    Hero* checkWinner();
    Character* targetEnemy();
    vector<int> boost(Card& card);
    void setPlayer1(const string& name, const int& age);
    void setPlayer2(const string& name, const int& age);
    const vector<string>& get_Avalable_Attack_Cards();
    const vector<string>& get_Avalable_Defence_Cards();
    Player* getCurrentPlayer();
    Player* getFirstPlayer();
    void choiceHero(Player& player, HeroType choice);
    Board& getBoard();
    void move(const int& pos);
    bool useAction();
    int getRemainingActions() const;
    vector<Character*> getAttackableTargets();
    void combat(const string& attackCard, const string& defendCard);
    
};