#include "Effects/Effects.hpp"
#include "Effects/Conditions.hpp"
#include "Ability/IAbility.hpp"
#include <cstdlib>
#include <algorithm>
using namespace std ;

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
        context.getGame()->requestAction(make_unique<MoveAction>(c , MoveMode::AnySpace , distance)) ;
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
    
    if(context.getDefenderCard() == context.getCurrentCard())
    {
        if(context.getEnemyPlayer()->getHero()->getAbility()->allowCancel(context.getAttackerCard(),context))
        {
            context.getAttackerCard()->getEffects().clear(); 
            return ;
        }
    }
    if(context.getAttackerCard() == context.getCurrentCard())
    {
        if(context.getEnemyPlayer()->getHero()->getAbility()->allowCancel(context.getDefenderCard(),context))
        {
            context.getDefenderCard()->getEffects().clear(); 
            return ;
        }
    }
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
            if(context.getGame()->canMove(c2))
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

void ReviveSister::execute(GameContext& context ,  const vector<Character*>& targets)
{
    for(auto sister : targets)
    {
        if(!sister->isAlive())
        {
            sister->heal(sister->getMaxhp()) ;
            context.getGame()->requestAction(make_unique<MoveAction>(sister , MoveMode::Zone ,
                 context.getCurrentPlayer()->getHero()->getPosition()));
        }
    }   
}

void AmbushEffect::execute(GameContext& context ,  const vector<Character*>& targets)
{
    int randomindex = (rand())%(context.getEnemyPlayer()->getHero()->getDeck()->getHandSize());
    Card* randomcard = context.getEnemyPlayer()->getHero()->getDeck()->previewCard(randomindex);
    context.getCurrentCard()->setValue(context.getCurrentCard()->getValue() + randomcard->getBoost()) ;
    context.getEnemyPlayer()->getHero()->getDeck()->discardFromHand(randomindex);
}

void GainActionEffect::execute(GameContext& context ,  const vector<Character*>& targets)
{
    context.getGame()->addAction() ;
}

void FeedingFrenzyEffect::execute(GameContext& context ,  const vector<Character*>& targets)
{
    int count = 0 ; 
    for(auto sister : targets)
    {
        if(areInSameZone(context.getBoard() , context.getDefender() , sister))
        {
            count++ ;
        }
    }
    context.getAttackerCard()->setValue(context.getAttackerCard()->getValue() + count) ;
}

void RaveningSeduction::execute(GameContext& context , const vector<Character*>& targets)
{
    // افککتشو نزدم 
}

void PreyUponEffect::execute(GameContext& context , const vector<Character*>& targets)
{
    int count = 0 ;
    for(auto opponet : targets)
    {
        if(areAdjacent(context.getBoard() , context.getAttacker() , opponet))
        {
            opponet->takeDamage(1) ;
            count++ ;
        }
    }
    context.getAttacker()->heal(count) ;
}

void LookIntoMyEyesEffect::execute(GameContext& context , const vector<Character*>& targets)
{
    context.getDefenderCard()->setValue(context.getDefenderCard()->getValue() + context.getAttackerCard()->getBoost()) ;
}

void ThirstEffect::execute(GameContext& context , const vector<Character*>& targets)
{
    for(auto c : targets)
    {
        context.getGame()->requestAction(make_unique<MoveAction>(c ,MoveMode::Zone , context.getDefender()->getPosition())) ;
    }
}

void RaveningEffect::execute(GameContext& context , const vector<Character*>& targets)
{
    int count ;
    for(auto sister : targets)
    {
        if(areAdjacent(context.getBoard() , context.getSelectedCharacter() , sister))
        {
            count++ ;
        }
    }
    context.getSelectedCharacter()->takeDamage(count) ;
}

void BeastFormEffect::execute(GameContext& context , const vector<Character*>& targets)
{
    auto indexes = context.getSelectedCardsIndex() ;
    sort(indexes.rbegin() , indexes.rend()); 
    int count = 0 ; 
    for(auto index : indexes)
    {
        context.getCurrentPlayer()->getHero()->getDeck()->discardFromHand(index) ;
        count++ ;
    }
    context.getAttackerCard()->setValue(context.getAttackerCard()->getValue() + count) ;
}