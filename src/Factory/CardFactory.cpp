#include "Factory/CardFactory.hpp"
#include "Effects/Effects.hpp"
#include "Effects/Conditions.hpp"
using namespace std ;

shared_ptr<Card> CardFactory::createCard(
    const string & name ,
    CardType type , 
    FighterType fighter , 
    TriggerType trigger ,
    int value , 
    int boost , 
    const string& description
)
{
    return make_shared<Card>(
        name,
        type,
        fighter,
        trigger,
        value,
        boost,
        description
    );
}

void CardFactory::addCopies(
    std::shared_ptr<Deck> deck,
    int count,
    const std::shared_ptr<Card>& card)
{
    for (int i = 0; i < count; i++)
    {
        deck->addcard(
            std::make_shared<Card>(*card)
        );
    }
}
shared_ptr<Deck> CardFactory::createSherlockDeck()
{
    auto deck = make_shared<Deck>() ;
    auto AdministerAid = createCard(
        "Administer Aid" ,
        CardType::Scheme , 
        FighterType::Sidekick , 
        TriggerType::None , 
        0 , 
        2 ,
        "Place Dr.Watson in a space adjacent to Holmes. Holmes recovers 1 Health. Draw 1 Card" 
    ) ;
    AdministerAid->addEffect(
        TriggerType::None , EffectTarget::FriendlyHero , nullptr , make_shared<HealEffect>(1)
    );
    AdministerAid->addEffect(
        TriggerType::None , EffectTarget::currentPlayer , nullptr  ,make_shared<DrawCardEffect>(1)
    );
    // move ro felan namizanam
    addCopies(deck ,2 , AdministerAid) ;

    auto ServiceRevolver = createCard(
        "Service Revolver" , 
        CardType::Attack , 
        FighterType::Sidekick , 
        TriggerType::None ,  
        5 , 
        3 ,
        "No description"
    ) ;
    addCopies(deck , 2 , ServiceRevolver) ;



    /*auto FPIACA = createCard(
        "Fixed Point In A Changing Age" , 
        CardType::Versalite ,
        FighterType::Sidekick , 
        TriggerType::AfterCombat , 
        EffectTarget::
    );*/

    deck->shuffleDeck();
    return deck ;
}

shared_ptr<Deck> CardFactory::createDraculaDeck()
{
    auto deck = std::make_shared<Deck>();
    /*auto mistform = createCard(
        "Mistform",
        CardType::Scheme,
        FighterType::Hero,
        TriggerType::Immediately,
        EffectTarget::anycharacter,
        0,
        2,
        "Place Dracula in any space. Gain 1 action."
    );*/
    // mistform->addEffect(std::make_shared<MoveEffect>(...));
    // mistform->addEffect(std::make_shared<GainActionEffect>(1));
    //addCopies(deck,1,mistform);
    deck->shuffleDeck();
    return deck;
}