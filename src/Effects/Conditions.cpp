#include "Effects/Conditions.hpp"
#include <algorithm>
using namespace std; 

bool areAdjacent( Board* board , const Character* first , const Character* Second) 
{
    const auto& neighbors = board->getSpace(first->getPosition()).neighbors ;
    return (find(neighbors.begin(), neighbors.end() , Second->getPosition()) != neighbors.end()) ;
}

bool areInSameZone(Board* board , const Character* first , const Character* Second)
{
    const auto& firstZone = board->getSpace(first->getPosition()).zone;
    const auto& SecondZone = board->getSpace(Second->getPosition()).zone ; 
    for(int zone : firstZone)
    {
        if(find(SecondZone.begin() , SecondZone.end() , zone) != SecondZone.end())
        {
            return true ;
        }
    }
    return false ; 
}

bool AdjacentCondition::check(GameContext& context) const
{
    return areAdjacent(context.board , context.currentPlayer->getHero() , context.enemyPlayer->getHero()); 
}

