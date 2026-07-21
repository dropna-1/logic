#pragma once
#include "ui/Actions/IAction.hpp"
#include "Common/Option.hpp"
#include <vector>
#include <optional>

class Card;
class Character;

class CombatAction : public IAction {
public:
    explicit CombatAction(Game* game);
    ftxui::Component GetComponent() override;

private:

    std::vector<AttackOption> combatOptions_;

    AttackOption selectedCombat_;

    std::vector<Option> attackCards_;
    std::vector<Option> defenseCards_;

    int selectedAttackCard_ = -1;
    std::optional<int> selectedDefenseCard_ = std::nullopt;

private:

    void SelectCombat();
    void SelectAttackCard();
    void SelectDefenseCard();
    void HandlePendingAction();

};