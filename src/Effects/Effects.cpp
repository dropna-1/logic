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
    for(auto c : targets)
    {
        auto places = context.getGame()->getAvailableMoves(c , 3) ;
        for(auto c2 : places)
        {
            if(context.getGame()->canMove(c2 , places))
            {
                c->setPosition(c2) ;
            }
        }
    }
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

void SwapEffect::execute(GameContext& context , const vector<Character*>& targets)
{
    auto SecondTarget = context.getTargets(EffectTarget::EnemyHero) ;
    for(auto c1 : targets)
    {
        for(auto c2 : SecondTarget)
        {
            auto temp = c1->getPosition() ;
            c1->setPosition(c2->getPosition()) ;
            c2->setPosition(temp) ;
        }
    }
}

void MoveToAdjacentEffect::execute(GameContext& context , const vector<Character*>& targets)
{
    for(auto c : targets) 
    {
        auto places = context.getBoard()->getSpace(c->getPosition()).neighbors ;
        for(auto c2 : places)
        {
            if(context.getGame()->canMove(c2,places))
            {
                c->setPosition(c2) ;
            }
        }
    }
}

void DeduceEffect::execute(GameContext& context , const vector<Character*>& targets)
{
    if(context.getCurrentCard() == context.getDefenderCard())
    {
        int temp = context.getAttackerCard()->getBoost() ;
        context.getAttackerCard()->setBoost(context.getAttackerCard()->getValue()) ;
        context.getAttackerCard()->setValue(temp) ;
        return ;
    }
    if(context.getCurrentCard() == context.getAttackerCard())
    {
        int temp = context.getDefenderCard()->getBoost() ;
        context.getDefenderCard()->setBoost(context.getDefenderCard()->getValue()) ;
        context.getDefenderCard()->setValue(temp) ;
        return ;
    }
}