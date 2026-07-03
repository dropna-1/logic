#pragma once
#include <iostream>
#include "include/Characters/Hero.hpp"
using namespace std;

class Player {
    string name;
    int age;
    Hero* hero = nullptr;
public:
    Player() = default;
    void setHero(const Hero& h);
    void setName(const string& n);
    void setAge(const int& a);
    Hero* getHero();
    int getAge();
    string getName();
};