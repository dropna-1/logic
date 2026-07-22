#pragma once

#include "ui/Actions/IAction.hpp"
#include <vector>

class Character;

class ManeuverAction : public IAction {
public:

    explicit ManeuverAction(Game* game);
    ftxui::Component GetComponent() override;

private:
    int movement_ = 0;

    Character* selectedCharacter_ = nullptr;
    std::vector<Option> boostCards_;
    std::vector<Option> availableMoves_;

    std::vector<std::shared_ptr<Card>> hand_;

    void SelectBoostCard();
    void SelectCharacter();
    void SelectDestination();
    void SelectDiscardCard();
};