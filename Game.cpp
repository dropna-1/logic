#include <algorithm>
#include "Game.hpp"

Game::Game() : self(&drakula), enemy(&Sherlock){}

vector<int> Game::moves(){
    vector<int> reachable;
    for(int i : board.getSpace(self->get_position()).neighbors){
        if(i == enemy->get_position()){continue;}
        reachable.push_back(i);
        for(int j : board.getSpace(i).neighbors){
            if(j == enemy->get_position() || j == self->get_position()){continue;}
            reachable.push_back(j);
        }
    }
    sort(reachable.begin(), reachable.end());
    reachable.erase(unique(reachable.begin(), reachable.end()), reachable.end()); 
    return reachable;
}

bool Game::canMove(int to, const vector<int>& reachable){
    for(int i : reachable)
        if(to == i)
            return true;
    return false;
}

void Game::changeTurn(){
    swap(self, enemy);
}

int main(){
    Game game;
    for(int k : game.moves())
        cout << k << endl;
    return 0;
}