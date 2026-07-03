#pragma once 

#include "Effects/IEffects.hpp"

class HealEffect : public IEffect
{
private:
    int heal;
public:
    HealEffect(int heal);
    int getHeal() const;
};

