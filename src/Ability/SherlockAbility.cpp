#include "Ability/SherlockAbility.hpp"
using namespace std ;

// esm o tozihat ability ro badan dorost mikonam
string SherlockAbility::getName() const
{
    return "Sherlock ability";
}

string SherlockAbility::getDescription() const
{
    return "Sherlock ABility";
}

bool SherlockAbility::allowCancel(Card* card , GameContext& context) 
{
    if(card->getFighter() == FighterType::Any)
    {
        return true ;
    }
    return false ;
}