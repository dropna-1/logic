#pragma once 

#include "board.hpp"
#include "Characters/Character.hpp"
#include "IConditions.hpp"

bool areAdjacent(const Board* board , const Character* first , const Character* Second) ;
bool areInSameZone(const Board* board , const Character* first , const Character* Second) ;
//bool IsInZone(const Board* board , const Character* first , int zone) ;

class AdjacentCondition : public IConditions
{
    private :
        ConditionTarget first ;
        ConditionTarget Second ;
    public :
        AdjacentCondition(ConditionTarget first , ConditionTarget Second) ;
        bool check(GameContext& context) const override ;
};