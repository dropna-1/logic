#include "ui/Actions/ManeuverAction.hpp"
#include "Cards/Deck.hpp"

#include "Game/Game.hpp"
#include <string>
#include <vector>


using namespace ftxui;


ManeuverAction::ManeuverAction(Game* game)
    : IAction(game)
{
    SelectCharacter();
}


ftxui::Component ManeuverAction::GetComponent()
{
    return menu_.GetComponent();
}


void ManeuverAction::SelectCharacter()
{
    if(!game_)
    {
        Finish();
        return;
    }


    std::vector<Character*> characters =
        game_->getCurrentPlayer()->getAllCharacters();

    std::vector<std::string> names;
    for(const auto& c : characters)
    {
        names.push_back(c->getname());
    }

    menu_.SetTitle("Select Character");
    menu_.SetItems(names);

    menu_.SetOnAccept(
        [this, characters](int index)
        {
            if(index < 0 ||
               index >= static_cast<int>(characters.size()))
            {
                Finish();
                return;
            }

            selectedCharacter_ = characters.at(index);

            if(!selectedCharacter_)
            {
                Finish();
                return;
            }

            movement_ = selectedCharacter_->getMovement();
            SelectBoostCard();
        }
    );

    menu_.SetOnCancel(
        [this](){Finish();}
    );
}


void ManeuverAction::SelectBoostCard()
{
    hand_ = game_->getCurrentPlayer()->getHero()->getDeck()->getHand();
    std::vector<std::string> items;

    for(int c = 0; c < hand_.size(); c++)
        items.push_back(hand_.at(c)->getName() + " (+" + 
        std::to_string(hand_.at(c)->getBoost()) + ")");

    items.push_back("Skip");

    menu_.SetTitle("Select Boost Card");
    menu_.SetItems(items);

    menu_.SetOnAccept(
        [this](int index)
        {
            if(index == static_cast<int>(hand_.size()))
            {
                SelectDestination();
                return;
            }

            movement_ =
                game_->boost(
                    selectedCharacter_,
                    index
                );

            SelectDestination();
        }
    );

    menu_.SetOnCancel(
        [this]()
        {
            SelectCharacter();
        }
    );
}



void ManeuverAction::SelectDestination()
{
    availableMoves_ =
        game_->getAvailableMoves(
            selectedCharacter_,
            movement_
        );

    if(availableMoves_.empty())
    {
        Finish();
        return;
    }

    std::vector<std::string> destinations;

    for(const auto& move : availableMoves_)
    {
        destinations.push_back(
            move.text + " " + std::to_string(move.id)
        );
    }

    menu_.SetTitle("Select Destination");
    menu_.SetItems(destinations);

    menu_.SetOnAccept(
        [this](int index)
        {

            if(index < 0 ||
               index >= static_cast<int>(availableMoves_.size()))
            {
                Finish();
                return;
            }

            game_->performManeuver(
                selectedCharacter_,
                availableMoves_[index].id
            );

            if(game_->getCurrentPlayer()->getHero()
            .get()->getDeck().get()->getHand().size() > 7)
                SelectDiscardCard();
            
            else
                Finish();
        }
    );
    menu_.SetOnCancel(
        [this](){Finish();}
    );
}

void ManeuverAction::SelectDiscardCard()
{
    auto& hand = game_->getCurrentPlayer()->getHero()
    .get()->getDeck().get()->getHand();

    std::vector<std::string> cards;

    for (auto& card : hand)
        cards.push_back(card.get()->getName());

    menu_.SetTitle("Discard a card");
    menu_.SetItems(cards);

    menu_.SetOnAccept([this, hand](int index)
    {
        if (index < 0 || index >= static_cast<int>(hand.size()))
        {
            Finish();
            return;
        }

        game_->getCurrentPlayer()->getHero().get()->getDeck().get()->discardFromHand(index);
        Finish();
    });

    menu_.SetOnCancel([this](){});
}