#include "Effects/Effects.hpp"

DamageEffect::DamageEffect(int damage) : damage(damage)
{
}

void DamageEffect::execute(GameContext& context, const vector<Character*>& targets)
{
    for(auto character : targets)
    {
        character->takeDamage(damage);
    }
}

HealEffect::HealEffect(int heal) : heal(heal)
{
}

void HealEffect::execute(GameContext& context,const vector<Character*>& targets)
{
    for(auto character : targets)
    {
        character->heal(heal);
    }
}

DrawCardEffect::DrawCardEffect(int count) : count(count) 
{
}

void DrawCardEffect::execute(GameContext& context, const vector<Character*>& targets )
{
    auto deck = context.getCurrentPlayer()->getHero()->getDeck() ;
    for(int i = 0 ; i < count ; i++)
    {
        deck->drawCard() ;
    }
}

MoveEffect::MoveEffect(int distance) : distance(distance)
{
}

void MoveEffect::execute(GameContext& context, const vector<Character*>& targets)
{
    //will do it later
}

DiscardCardEffect::DiscardCardEffect(int count) : count(count) 
{
}

void DiscardCardEffect::execute(GameContext& context, const vector<Character*>& targets )
{
    auto deck = context.getEnemyPlayer()->getHero()->getDeck() ;
    for(int i = 0 ; i < count ; i++)
    {
        deck->discardFromHand(count) ;
    }
}

void CancelEffectsEffect::execute(GameContext& context, const vector<Character*>& targets)
{
    if(context.getDefenderCard() == nullptr)
    {
        return ;
    }
    context.getDefenderCard()->getEffects().clear(); 
}
