#include "player.hpp"

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