#ifndef HERO_HPP
#define HERO_HPP

#include <iostream>
#include <memory>
#include <vector>
#include "Character.hpp"
#include "TypeEnums.hpp"

class Deck ;
class SideKick ; 
class IAbility ; 



class Hero : public Character 
{
    private :
        HeroType herotype ;
        std::shared_ptr<Deck> deck ;
        std::shared_ptr<IAbility> ability ;
        std::vector<std::shared_ptr<SideKick>> sidekicks ;
    public :
        Hero(const std::string& name , int hp , int movement , HeroType type) ;
        HeroType getHeroType() const ;
        std::shared_ptr<Deck> getdeck() ;
        std::shared_ptr<IAbility> getability() ;
        std::vector<std::shared_ptr<SideKick>>& getSidekicks() ;
        void setDeck(std::shared_ptr<Deck> deck) ;
        void setAbility(std::shared_ptr<IAbility> ability) ;
        void addSidekick(std::shared_ptr<SideKick> sidekick) ;
        void printInfo() const override ;
};

#endif 