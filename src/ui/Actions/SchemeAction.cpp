#include "ui/Actions/SchemeAction.hpp"
#include "Game/Game.hpp"

#include <ftxui/component/component.hpp>

using namespace ftxui;

SchemeAction::SchemeAction(Game* game)
    : IAction(game)
{
    SelectHero();
}

Component SchemeAction::GetComponent()
{
    if(pending_handler_)
        return pending_handler_->GetComponent();

    return menu_.GetComponent();
}

void SchemeAction::SelectHero()
{
    if(!game_)
    {
        Finish();
        return;
    }

    heroes_.clear();
    std::vector<std::string> options;

    for(Character* character : game_->getCurrentPlayer()->getAllCharacters())
    {
        auto cards = game_->getSchemeCards(character);

        if(cards.empty())
            continue;

        heroes_.push_back(character);
        options.push_back(character->getname());
    }

    if(heroes_.empty())
    {
        Finish();
        return;
    }

    menu_.SetTitle("Select Hero");
    menu_.SetItems(options);

    menu_.SetOnAccept(
        [this](int index)
        {
            if(index < 0 ||
               index >= static_cast<int>(heroes_.size()))
            {
                Finish();
                return;
            }

            selectedHero_ = heroes_.at(index);
            SelectSchemeCard();
        }
    );

    menu_.SetOnCancel(
        [this]()
        {
            Finish();
        }
    );
}

void SchemeAction::SelectSchemeCard()
{
    schemeCards_ = game_->getSchemeCards(selectedHero_);

    std::vector<std::string> options;

    for(const auto& card : schemeCards_)
        options.push_back(card.text);

    menu_.SetTitle("Select Scheme Card");
    menu_.SetItems(options);

    menu_.SetOnAccept(
        [this](int index)
        {
            if(index < 0 ||
               index >= static_cast<int>(schemeCards_.size()))
            {
                Finish();
                return;
            }

            selectedCard_ = index;
            game_->playScheme(selectedHero_, selectedCard_);

            if(game_->hasPendingAction())
            {
                pending_handler_ =
                    std::make_unique<PendingActionHandler>(
                        game_,
                        [this](){Finish();},
                        [this]()
                        {
                            game_->playScheme(
                                selectedHero_,
                                selectedCard_
                            );
                        }
                    );
            }
            else{
                Finish();
            }
        }
    );

    menu_.SetOnCancel(
        [this]()
        {
            SelectHero();
        }
    );
}