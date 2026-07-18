#include "Ability/DraculaAbility.hpp"

// inam esm o tozihatesho badan misazam
std::string DraculaAbility::getName() const
{
    return "Draculaaaaa";
}

std::string DraculaAbility::getDescription() const
{
    return "dadadadraaacilaalal";
}

void DraculaAbility::execute(Character* target)
{
    target->takeDamage(1) ;
}