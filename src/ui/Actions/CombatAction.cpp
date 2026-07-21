#include "ui/Actions/CombatAction.hpp"
#include "Game/Game.hpp"
#include <ftxui/component/component.hpp>
#include <string>
using namespace ftxui;

CombatAction::CombatAction(Game* game)
    : IAction(game)
{
    SelectCombat();
}

ftxui::Component CombatAction::GetComponent()
{
    return menu_.GetComponent();
}

void CombatAction::SelectCombat()
{
    if(!game_)
    {
        Finish();
        return;
    }
    
    combatOptions_ = game_->getAttackableTargets();

    std::vector<std::string> options;

    for(const auto& combat : combatOptions_)
    {
        options.push_back(
            combat.attacker->getname() + " -> " +
            combat.target->getname()
        );
    }

    menu_.SetTitle("Select Combat");
    menu_.SetItems(options);

    menu_.SetOnAccept(
        [this](int index)
        {
            if(index < 0 ||
               index >= static_cast<int>(combatOptions_.size()))
            {
                Finish();
                return;
            }

            selectedCombat_ = combatOptions_[index];
            SelectAttackCard();
        }
    );

    menu_.SetOnCancel(
        [this]()
        {
            Finish();
        }
    );
}

void CombatAction::SelectAttackCard()
{
    attackCards_ =
        game_->getPlayableAttackCard(
            selectedCombat_.attacker
        );

    if(attackCards_.empty())
    {
        Finish();
        return;
    }

    std::vector<std::string> options;
    for(const auto& card : attackCards_)
    {
        options.push_back(card.text);
    }

    menu_.SetTitle("Select Attack Card By " + game_->getCurrentPlayer()->getName());
    menu_.SetItems(options);

    menu_.SetOnAccept(
        [this](int index)
        {
            if(index < 0 ||
               index >= static_cast<int>(attackCards_.size()))
            {
                Finish();
                return;
            }

            selectedAttackCard_ = index;

            if(game_->canDefense(selectedCombat_.target))
            {
                SelectDefenseCard();
            }
            else
            {
                game_->combat(
                    selectedCombat_,
                    selectedAttackCard_,
                    selectedAttackCard_
                );

                if(game_->hasPendingAction())
                    HandlePendingAction();
                else
                    Finish();
            }
        }
    );

    menu_.SetOnCancel(
        [this]()
        {
            SelectCombat();
        }
    );
}

void CombatAction::SelectDefenseCard()
{
    defenseCards_ =
        game_->getPlayableDefenseCard(
            selectedCombat_.target
        );

    std::vector<std::string> options;
    options.push_back("Do Not Defend");
    for (const auto& card : defenseCards_)
    {
        options.push_back(card.text);
    }

    menu_.SetTitle("Select Defense Card By " + game_->getCurrentPlayer()->getName());
    menu_.SetItems(options);

    menu_.SetOnAccept(
        [this](int index)
        {
            if(index < 0 ||
               index > static_cast<int>(defenseCards_.size()))
            {
                Finish();
                return;
            }

            if(index != 0)
                selectedDefenseCard_ = index-1;

            game_->combat(
                selectedCombat_,
                selectedAttackCard_,
                selectedDefenseCard_
            );

            if(game_->hasPendingAction())
                HandlePendingAction();
            else
                Finish();
        }
    );
    menu_.SetOnCancel(
        [this](){}
    );
}

void CombatAction::HandlePendingAction()
{
    if (!game_->hasPendingAction())
    {
        Finish();
        return;
    }
    auto* pending = game_->currentPendingAction();
    auto options = pending->getOption(*game_);

    std::vector<std::string> items;

    for (const auto& option : options)
        items.push_back(option.text + ' ' + std::to_string(option.id));

    menu_.SetTitle("Choose");
    menu_.SetItems(items);

    menu_.SetOnAccept(
        [this, pending, options](int index)
        {
            if(index < 0 ||
               index >= static_cast<int>(options.size()))
            {
                Finish();
                return;
            }

            pending->submit(*game_, options[index].id);
            if(!pending->isFinished())
                HandlePendingAction();

            game_->continueCombat();

            if(game_->hasPendingAction())
                HandlePendingAction();
            else
                Finish();
        }
    );

    menu_.SetOnCancel(
        [this](){}
    );
}