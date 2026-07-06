#ifndef IEFFECTS_HPP
#define IEFFECTS_HPP

class GameContext ; 
class Card ;

class IEffect
{
    public :
        virtual void execute(GameContext& context , Card& card) = 0 ;
        virtual ~IEffect() = default ;
};

#endif