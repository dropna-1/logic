#include "Factory/HeroFactory.hpp"
#include "Characters/Hero.hpp"
#include "Characters/SideKick.hpp"
#include "Factory/CardFactory.hpp"
#include "Ability/SherlockAbility.hpp"
#include "Ability/DraculaAbility.hpp"
using namespace std ;

shared_ptr<Hero> HeroFactory::createSherlock()
{
    auto hero = make_shared<Hero>("Sherlock" , 16, 2 , AttackType::Melee , HeroType::Sherlock ) ;
    hero->setDeck(CardFactory::createSherlockDeck()) ;
    hero->setAbility(std::shared_ptr<SherlockAbility>()) ;
    hero->addSidekick(make_shared<SideKick>("Dr.Watson" , 13  , 2 ,AttackType::Ranged)) ;
    return hero ;
}

shared_ptr<Hero> HeroFactory::createDracula()
{
    auto hero = make_shared<Hero>("Dracula" , 13 , 2, AttackType::Melee , HeroType::Dracula) ;
    hero->setDeck(CardFactory::createDraculaDeck()) ;
    hero->addSidekick(make_shared<SideKick>("Sister 1" , 1 , 2 , AttackType::Ranged)) ;
    hero->addSidekick(make_shared<SideKick>("Sister 2" , 1 , 2 , AttackType::Ranged)) ;
    hero->addSidekick(make_shared<SideKick>("Sister 3" , 1 , 2 , AttackType::Ranged)) ;
    return hero ;
}