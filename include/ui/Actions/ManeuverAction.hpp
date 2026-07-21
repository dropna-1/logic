#pragma once

#include "ui/Actions/IAction.hpp"
#include <vector>

class Character;

class ManeuverAction : public IAction {
public:

    explicit ManeuverAction(Game* game);
    ftxui::Component GetComponent() override;

private:

    Character* selectedCharacter_ = nullptr;
    std::vector<Option> availableMoves_;

    void SelectCharacter();
    void SelectDestination();
    void SelectDiscardCard();
};