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
    if(pending_handler_)
        return pending_handler_->GetComponent();
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
                {
                    pending_handler_ =
                        std::make_unique<PendingActionHandler>(
                            game_, 
                            [this](){Finish();},
                            [this](){game_->continueCombat();}
                        );
                }
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
            {
                pending_handler_ =
                    std::make_unique<PendingActionHandler>(
                        game_, 
                        [this](){Finish();},
                        [this](){game_->continueCombat();}
                    );
            }
            else
                Finish();
        }
    );
    menu_.SetOnCancel(
        [this](){}
    );
}