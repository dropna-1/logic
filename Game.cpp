#include <algorithm>
#include <queue>
#include "Game.hpp"

Game::Game() : self(&drakula), enemy(&Sherlock){}

vector<int> Game::moves(int move){
    vector<int> reachable;
    queue<pair<int, int>> q;
    vector<bool> visited(board.size(), false);

    int start = self->get_position();
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

            if(next == enemy->get_position())
                continue;

            visited[next] = true;
            reachable.push_back(next);
            q.push({next, dist+1});
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

int main(){
    Game game;
    for(int k : game.moves(2))
        cout << k << endl;
    return 0;
}