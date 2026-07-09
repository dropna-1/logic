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
        "Place Dr.Watson in a space adjacent to Holmes. Holmes recovers 1 Health. Draw 1 Card." 
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
        "No description."
    ) ;
    addCopies(deck , 2 , ServiceRevolver) ;

    auto FPIACA = createCard(
        "Fixed Point In A Changing Age" , 
        CardType::Versalite ,
        FighterType::Sidekick , 
        TriggerType::AfterCombat , 
        3 , 
        1 ,
        "AFTER COMBAT: If Dr.watson is adjacent to Holmes, they each recover 1 health."
    );
    FPIACA->addEffect(
        TriggerType::AfterCombat , EffectTarget::FriendlyCharacters , make_shared<AdjacentCondition>(
            ConditionTarget::FriendlyHero , ConditionTarget::FriendlySidekicks) , make_shared<HealEffect>(1));
    addCopies(deck , 2 , FPIACA) ;

    auto CounterPunch = createCard(
        "Counter Punch" ,
        CardType::Versalite , 
        FighterType::Hero , 
        TriggerType::AfterCombat , 
        3 , 
        1 , 
        "AFTER COMBAT: If Holmes is Adjacent to the opsing fighter, deal 2 Damage to that Fighter."
    );
    CounterPunch->addEffect(TriggerType::AfterCombat , EffectTarget::EnemyHero , 
        make_shared<AdjacentCondition>(ConditionTarget::FriendlyHero , ConditionTarget::EnemyHero) , make_shared<DamageEffect>(2));
    addCopies(deck , 3 , CounterPunch) ;

    auto EducationNeverEnds = createCard(
        "Education Never Ends" ,
        CardType::Versalite , 
        FighterType::Any , 
        TriggerType::AfterCombat , 
        3 , 
        1 , 
        "AFTER COMBAT: If you won the combat your opponet draws 1 card, if you lost thecombat you draw 2 cards."
    );
    EducationNeverEnds->addEffect(TriggerType::AfterCombat , EffectTarget::EnemyHero , 
        make_shared<WonBattleCondition>(ConditionTarget::FriendlyHero) , make_shared<DrawCardEffect>(1) ) ;
    EducationNeverEnds->addEffect(TriggerType::AfterCombat , EffectTarget::EnemyHero , 
        make_shared<LossBattleCondition>(ConditionTarget::FriendlyHero) , make_shared<DrawCardEffect>(2) ) ;
    addCopies(deck , 2 , EducationNeverEnds) ;

    auto EliminateTheImpossible = createCard(
        "Eliminate The Impossible" ,
        CardType::Scheme , 
        FighterType::Hero ,
        TriggerType::None , 
        0 , 
        2 ,
        "Choose one opponet, look at their card hand and choose 1 card for them to discard." 
    );
    EliminateTheImpossible->addEffect(TriggerType::None , EffectTarget::EnemyHero ,
        nullptr , make_shared<DiscardCardEffect>(1)) ;
    addCopies(deck , 2 , EliminateTheImpossible);

    auto Feint = createCard(
        "Feint" ,
        CardType::Versalite ,
        FighterType::Any ,
        TriggerType::Immediately , 
        2 ,
        1 ,
        "IMMEDIATELY: Cancel all effects on your opponet's card."
    );
    Feint->addEffect(TriggerType::Immediately , EffectTarget::EnemyHero , nullptr , make_shared<CancelEffectsEffect>());
    addCopies(deck , 3 , Feint); 

    

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