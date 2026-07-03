#pragma once
#include "Effects/IEffects.hpp"

class MoveEffect : public IEffect
{
private:
    int distance;
public:
    MoveEffect(int distance);
    int getDistance() const;
};
