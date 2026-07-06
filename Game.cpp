#include <algorithm>
#include <queue>
#include "include/Characters/SideKick.hpp"
#include "Game.hpp"
#include "Cards/Deck.hpp"

Game::Game() : dracula(HeroFactory::createDracula())
, sherlock(HeroFactory::createSherlock()){}

void Game::setPlayer1(const string& name, const int& age){
    player1.setName(name);
    player1.setAge(age);
}

void Game::setPlayer2(const string& name, const int& age){
    player2.setName(name);
    player2.setAge(age);
}

Player* Game::getFirstPlayer(){
    if(player1.getAge() <= player2.getAge())
        return &player1;
    return &player2;
}

void Game::choiceHero(Player& player, HeroType choice){
    player.setHero((choice == dracula.get()->getHeroType() ? dracula : sherlock));
}

void Game::startGame(){
    actionsRemaining = 2;
    if(player1.getAge() <= player2.getAge()){
        self = player1.getHero().get();
        enemy = player2.getHero().get();
    }
    else{
        enemy = player1.getHero().get();
        self = player2.getHero().get();
    }
    for(int i = 0; i < 10; i++)
        (i < 5 ? self : enemy)->getDeck().get()->drawCard();
}

Player* Game::getCurrentPlayer(){
    if(self == player1.getHero().get())
        return &player1;
    return &player2;
}

Board& Game::getBoard(){
    return board;
}

bool Game::useAction(){
    if(actionsRemaining == 0)
        return false;
    actionsRemaining--;
    return true;
}

int Game::getRemainingActions() const{
    return actionsRemaining;
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

const vector<string>& Game::get_Avalable_Attack_Cards(){
    vector<string> availableCards;
    for(auto card : self->getDeck().get()->getHand())
        if(card.get()->getType() == CardType::Attack 
        || card.get()->getType() == CardType::Multiple)
            availableCards.push_back(card.get()->getName());
    return availableCards;
}

const vector<string>& Game::get_Avalable_Defence_Cards(){
    vector<string> availableCards;
    for(auto card : self->getDeck().get()->getHand())
        if(card.get()->getType() == CardType::Defend 
        || card.get()->getType() == CardType::Multiple)
            availableCards.push_back(card.get()->getName());
    return availableCards;
}

void Game::move(const int& pos){
    self->setPosition(pos);
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
            if(j->getPosition() == i)
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