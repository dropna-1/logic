#include "Factory/CardFactory.hpp"
#include "Effects/DamageEffect.hpp"
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
    auto card = createCard(
        "kart test" ,
        CardType::Attack , 
        FighterType::Hero , 
        TriggerType::Immediately , 
        3 ,
        2 ,
        "it is for test" 
    ) ;
    card->addEffect(
        make_shared<DamageEffect>(3) 
    );
    deck->addcard(card) ;
    deck->shuffleDeck();
    return deck ;
}

shared_ptr<Deck> CardFactory::createDraculaDeck()
{
    auto deck = std::make_shared<Deck>();
    auto mistform = createCard(
        "Mistform",
        CardType::Scheme,
        FighterType::Hero,
        TriggerType::Immediately,
        0,
        2,
        "Place Dracula in any space. Gain 1 action."
    );
    // mistform->addEffect(std::make_shared<MoveEffect>(...));
    // mistform->addEffect(std::make_shared<GainActionEffect>(1));
    addCopies(deck,1,mistform);
    deck->shuffleDeck();
    return deck;
}