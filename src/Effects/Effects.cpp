#include "Effects/Effects.hpp"

DamageEffect::DamageEffect(int damage) : damage(damage)
{
}

void DamageEffect::execute(GameContext& context, Card& card)
{
    if(context.getTarget())
    {
        context.getTarget()->takeDamage(damage);
    }
}

HealEffect::HealEffect(int heal) : heal(heal) 
{
}

void HealEffect::execute(GameContext& context, Card& card)
{
    if(context.getTarget())
    {
        context.getTarget()->heal(heal);
    }
}

DrawCardEffect::DrawCardEffect(int count) : count(count) 
{
}

void DrawCardEffect::execute(GameContext& context, Card& card)
{
    auto deck = context.getCurrentHero()->getDeck() ;
    for(int i = 0 ; i < count ; i++)
    {
        deck->drawCard() ;
    }
}

