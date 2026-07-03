#include <algorithm>
#include <queue>
#include "include/Characters/SideKick.hpp"
#include "Game.hpp"

// Game::Game() : self(&drakula), enemy(&Sherlock){}

vector<int> Game::moves(const int& move){
    vector<int> reachable;
    queue<pair<int, int>> q;
    vector<bool> visited(board.size(), false);

    int start = self->getPosition();
    q.push({start, 0});
    visited[start] = true;

    while(!q.empty()){
        auto current = q.front();
        q.pop();

        int place = current.first;
        int dist = current.second;

        if(dist == move)
            continue;

        for(int next : board.getSpace(place).neighbors){
            if(visited[next])
                continue;

            if(next == enemy->getPosition())
                continue;

            visited[next] = true;
            reachable.push_back(next);
            q.push({next, dist+1});
        }

        if(!board.getSpace(place).secrets.empty()){
            for(int next : board.getSpace(place).secrets){
                if(visited[next])
                    continue;

                if(next == enemy->getPosition())
                    continue;

                visited[next] = true;
                reachable.push_back(next);
                q.push({next, dist+1});
            }
        }
    }
    sort(reachable.begin(), reachable.end());
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

Hero* Game::checkWinner(){
    if(!self->isAlive())
        return enemy;
    if(!enemy->isAlive())
        return self;
    return nullptr;
}

Character* Game::targetEnemy(){
    for(int i : board.getSpace(self->getPosition()).neighbors){
        if(enemy->getPosition() == i)
            return enemy;
        for(auto j : enemy->getSidekicks())
            if(j.get()->getPosition() == i)
                return j.get();
    }
    return nullptr;
}

int main(){
    Game game;
    for(int k : game.moves(2))
        cout << k << endl;
    return 0;
}