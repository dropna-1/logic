#include "Cards/Cards.hpp"
#include "Pending.hpp"
using namespace std ;

Card::Card(const string& name,
           CardType type,
           FighterType fighter,
           TriggerType trigger ,
           int value,
           int boost,
           const string& description)
    : name(name),
      type(type),
      fighter(fighter),
      trigger(trigger) ,
      value(value),
      boost(boost),
      description(description) 
{
}

const string& Card::getName() const
{
    return name;
}

CardType Card::getType() const
{
    return type;
}

FighterType Card::getFighter() const
{
    return fighter;
}

TriggerType Card::getTrigger() const
{
    return trigger;
}

int Card::getValue() const
{
    return value;
}

int Card::getBoost() const
{
    return boost;
}

const string& Card::getDescription() const
{
    return description;
}

const vector<EffectEntry>& Card::getEffects() const
{
    return effects;
}

vector<EffectEntry>& Card::getEffects() 
{
    return effects;
}

void Card::addEffect(TriggerType trigger,EffectTarget target,shared_ptr<IConditions> condition,shared_ptr<IEffect> effect)
{
    effects.push_back({trigger , target , condition , effect});
}

void Card::setBoost(int New)
{
    boost = New ;
}

void Card::setValue(int New)
{
    value = New ;
}
void Card::execute(TriggerType trigger , GameContext& context)
{
    for(const auto& entry : effects)
    {
        if(entry.trigger != trigger)
        {
            continue; 
        }
        if(entry.condition)
        {
            if(!entry.condition->check(context))
            {
                continue ;
            }
        }
        auto targets = context.getTargets(entry.target) ;
        entry.effect->execute(context , targets) ;
    }
}

void Card::addRequest(RequestEntry request)
{
    requests.push_back(request) ;   
}

void Card::applyRequest(RequestType requesti , GameContext& context)
{
    for(const auto& request : requests)
    {
        switch(request.type) 
        {
            case RequestType::Move :
            {
                context.getGame()->requestAction(make_unique<MoveAction>(context.getSelectedCharacter() , request.mode , request.MoveRange));
                break ;
            }
            case RequestType::Ravening :
            {
                context.getGame()->requestAction(make_unique<RaveningAction>(context.getGame())) ;
                break ;
            }
            case RequestType::Card :
            {
                switch(request.target)
                {
                    case EffectTarget::currentPlayer :
                    {
                        context.getGame()->requestAction(make_unique<ChooseCardAction>(context.getCurrentPlayer())) ;
                        break;
                    }
                    case EffectTarget::EnemyPlayer :
                    {
                        context.getGame()->requestAction(make_unique<ChooseCardAction>(context.getEnemyPlayer())) ;
                        break;
                    }
                }
                break; 
            }
            case RequestType::None :
            {
                break ;
            }
        }
    }
}