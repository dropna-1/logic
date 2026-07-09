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
        void execute(GameContext& context , const vector<Character*>& targets) override ;
};

class DrawCardEffect : public IEffect
{
    private:
        int count ;
    public:
        DrawCardEffect(int count);
        void execute(GameContext& context , const vector<Character*>& targets) override ;
};

class HealEffect : public IEffect
{   
    private:
        int heal;
    public:
        HealEffect(int heal);
        void execute(GameContext& context , const vector<Character*>& targets) override ;
};

class MoveEffect : public IEffect
{
    private:
        int distance;
    public:
        MoveEffect(int distance);
        void execute(GameContext& context , const vector<Character*>& targets) override ;
};

class DiscardCardEffect : public IEffect
{
    private :
        int count ;
        DiscardCardEffect(int count) ;
        void execute(GameContext& context , const vector<Character*>& targets) override ;
};

class CancelEffectsEffect : public IEffect
{
    public :
        void execute(GameContext& context , const vector<Character*>& targets) override ;   
};