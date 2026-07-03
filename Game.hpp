#pragma once
#include <iostream>
#include <vector>
#include "board.hpp"
#include "include/Characters/Hero.hpp"
using namespace std;

class Game {
    Board board;
    Hero drakula;
    Hero Sherlock;

    Hero* self;
    Hero* enemy;
public:
    Game();
    vector<int> moves(const int& move);
    bool canMove(int to, const vector<int>& reachable);
    void changeTurn();
    Hero* checkWinner();
    Character* targetEnemy();
};