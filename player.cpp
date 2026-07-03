#include "player.hpp"

void Player::setHero(const Hero& h){
    *hero = h;
}

void Player::setName(const string& n){
    this->name = n;
}

void Player::setAge(const int& a){
    this->age = a;
}

Hero* Player::getHero(){
    return hero;
}

int Player::getAge(){
    return age;
}

string Player::getName(){
    return name;
}