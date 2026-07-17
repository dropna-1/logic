#ifndef CARD_HPP
#define CARD_HPP

#include <iostream>
#include <vector> 
#include <memory>
#include "Enums/TypeEnums.hpp"
#include "Effects/IConditions.hpp"
#include "Effects/IEffects.hpp"


struct EffectEntry
{
    TriggerType trigger ;
    EffectTarget target ;
    std::shared_ptr<IConditions> condition;
    std::shared_ptr<IEffect> effect ;
};

struct RequestEntry
{
    RequestType type ;
    MoveMode mode = MoveMode::AnySpace ;
    EffectTarget target ;
    int MoveRange = 0 ; 
    int count = 0 ;
};


class Card 
{
    private:
        std::string name ; 
        CardType type ; 
        TriggerType trigger ;
        FighterType fighter ;
        int value ;
        int boost ;
        std::string description ;
        std::vector<EffectEntry> effects ;
        std::vector<RequestEntry> requests ;
    public :
        Card(const std::string& name,
            CardType type,
            FighterType fighter,
            TriggerType trigger , 
            int value,
            int boost ,
            const std::string& description);
        void addEffect(TriggerType , EffectTarget , std::shared_ptr<IConditions> , shared_ptr<IEffect>) ;
        const std::string& getName() const;
        int getValue() const;
        int getBoost() const;
        CardType getType() const;
        FighterType getFighter() const;
        TriggerType getTrigger() const;
        const std::string& getDescription() const ;
        std::vector<EffectEntry>& getEffects() ;
        const std::vector<EffectEntry>& getEffects() const ;
        const std::vector<RequestEntry>& getRequests() const ;
        void execute(TriggerType , GameContext&) ;
        void applyRequest(RequestType , GameContext&) ;
        void setBoost(int) ;
        void setValue(int) ;
        void addRequest(RequestEntry) ;
            
};


#endif