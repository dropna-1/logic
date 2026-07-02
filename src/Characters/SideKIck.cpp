#include "Characters/SideKick.hpp"

SideKick::SideKick(const std::string& name, int health, int movement) : Character(
    name, 
    health, 
    movement) 
{
}

void SideKick::printInfo() const
{
    std::cout << "Sidekick : " << name << '\n';
    std::cout << "Health   : " << hp
              << "/" << maxHp << '\n';
}