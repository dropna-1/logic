#ifndef IEFFECTS_HPP
#define IEFFECTS_HPP

class GameContext ; 

class IEffect
{
    public :
        virtual void execute(GameContext& context) = 0 ;
        virtual ~IEffect() = default ;
};

#endif