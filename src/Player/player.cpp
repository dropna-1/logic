#include "Player/player.hpp"
#include "Characters/SideKick.hpp"
#include "Characters/Hero.hpp"


void Player::setHero(shared_ptr<Hero> hero){
    this->hero = hero;
}

void Player::setName(const string& n){
    this->name = n;
}

void Player::setAge(const int& a){
    this->age = a;
}

shared_ptr<Hero> Player::getHero(){
    return hero;
}

int Player::getAge(){
    return age;
}

string Player::getName(){
    return name;
}

vector<Character*> Player::getAllCharacters(){
    vector<Character*> characters{hero.get()};
    for(auto sidekick : hero.get()->getSidekicks())
        characters.push_back(sidekick.get());
    return characters;
}
