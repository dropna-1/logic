#include <algorithm>
#include <queue>
#include "include/Characters/SideKick.hpp"
#include "Game.hpp"
#include "Cards/Deck.hpp"

Game::Game() : drakula(HeroFactory::createDracula())
, sherlock(HeroFactory::createSherlock()){}

void Game::startGame(){
    string p1Name, p2Name;
    int p1Age, p2Age;

    cout << "Player1:\nEnter Your Name" << endl;
    cin >> p1Name;
    cout << "Enter Your Age" << endl;
    cin >> p1Age;


    player1.setName(p1Name);
    player1.setAge(p1Age);

    cout << "Player2:\nEnter Your Name" << endl;
    cin >> p2Name;
    cout << "Enter Your Age" << endl;
    cin >> p2Age;

    player2.setName(p2Name);
    player2.setAge(p2Age);


    for(int i = 0; i < 10; i++)
        (i < 5 ? self : enemy)->getDeck().get()->drawCard();
}

vector<int> Game::getAvailableMoves(const int& move){
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
            for(auto sidekick : enemy->getSidekicks())
                if(next == sidekick.get()->getPosition())
                    continue;

            visited[next] = true;
            q.push({next, dist+1});

            for(auto sidekick : self->getSidekicks())
                if(next == sidekick.get()->getPosition())
                    continue;    
            reachable.push_back(next);
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

vector<int> Game::free_spaces_for_Sidekicks(){
    vector<int> reachable;
    for(int zone : board.getSpace(self->getPosition()).zone){
        for(int i = 0; i < 32; i++){
            if(i == self->getPosition())
                continue;
            vector<int> zones = board.getSpace(i).zone;
            if(find(zones.begin(), zones.end(), zone) != zones.end())
                reachable.push_back(i);
        }
    }
    return reachable;
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

vector<int> Game::boost(Card& card){
    int move = self->getMovement();
    move += card.getBoost();
    return getAvailableMoves(move);
}

// int main(){
//     Game game;
//     for(int k : game.getAvailableMoves(2))
//         cout << k << endl;
//     return 0;
// }