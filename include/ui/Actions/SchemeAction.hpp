#pragma once

#include "ui/Actions/IAction.hpp"
#include "ui/SelectionMenu.hpp"
#include "ui/Actions/PendingActionHandler.hpp"

#include <vector>
#include <memory>

class Character;

class SchemeAction : public IAction
{
public:
    explicit SchemeAction(Game* game);

    ftxui::Component GetComponent() override;

private:
    void SelectHero();
    void SelectSchemeCard();

private:
    SelectionMenu menu_;

    std::vector<Character*> heroes_;
    Character* selectedHero_ = nullptr;

    std::vector<Option> schemeCards_;
    int selectedCard_ = -1;

    std::unique_ptr<PendingActionHandler> pending_handler_;
};