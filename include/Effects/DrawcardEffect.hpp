#pragma once
#include "Effects/IEffects.hpp"

class DrawCardEffect : public IEffect
{
private:
    int amount;
public:
    DrawCardEffect(int amount);
    int getAmount() const;
};
