#pragma once

#include "IEffects.hpp"
#include "GameContext.hpp"
#include "Cards/Deck.hpp"

class DamageEffect : public IEffect
{
    private :
        int damage ;
    public :
        DamageEffect(int damage) ;
        void execute(GameContext& context , Card& card) override ;
};

class DrawCardEffect : public IEffect
{
    private:
        int count ;
    public:
        DrawCardEffect(int count);
        void execute(GameContext& context , Card& card) override ;
};

class HealEffect : public IEffect
{
    private:
        int heal;
    public:
        HealEffect(int heal);
        void execute(GameContext& context , Card& card) override ;
};

class MoveEffect : public IEffect
{
private:
    int distance;
public:
    MoveEffect(int distance);
    int getDistance() const;
};