#ifndef CARD_HPP
#define CARD_HPP

#include <iostream>
#include <vector> 
#include <memory>
#include "Enums/TypeEnums.hpp"

class IEffect ;

class Card 
{
    private:
        std::string name ; 
        CardType type ; 
        FighterType fighter ;
        TriggerType trigger ;
        int value ;
        int boost ;
        std::vector<std::shared_ptr<IEffect>> effects ;
    public :
        Card(const std::string& name,
            CardType type,
            FighterType fighter,
            TriggerType trigger,
            int value,
            int boost);
         void addEffect(std::shared_ptr<IEffect> effect);
    const std::string& getName() const;
    int getValue() const;
    int getBoost() const;
    CardType getType() const;
    FighterType getFighter() const;
    TriggerType getTrigger() const;
    const std::vector<std::shared_ptr<IEffect>>& getEffects() const;
            
};


#endif