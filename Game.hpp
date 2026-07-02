#pragma once
#include <iostream>
#include <vector>
#include "board.hpp"
#include "Heroes.hpp"
using namespace std;

class Game {
    Board board;
    Drakula drakula;
    Sherlock Sherlock;

    Hero* self;
    Hero* enemy;
public:
    Game();
    vector<int> moves();
    bool canMove(int to, const vector<int>& reachable);
    void changeTurn();
};