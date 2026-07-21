#pragma once

#include "Game/Game.hpp"
#include "ui/SelectionMenu.hpp"

#include <ftxui/component/component.hpp>

class IAction {
public:
    explicit IAction(Game* game)
        : game_(game) {}

    virtual ~IAction() = default;

    virtual ftxui::Component GetComponent() = 0;

    bool IsFinished() const {
        return finished_;
    }

protected:
    Game* game_;
    SelectionMenu menu_;

    bool finished_ = false;

    void Finish() {
        finished_ = true;
    }
};