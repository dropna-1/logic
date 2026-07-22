#pragma once
#include <functional>
#include <vector>

#include <ftxui/component/component.hpp>
#include "ui/SelectionMenu.hpp"
#include "Common/Option.hpp"

class Game;

class PendingActionHandler {
public:
    PendingActionHandler(
        Game* game,
        std::function<void()> on_finish,
        std::function<void()> on_submit
    );

    ftxui::Component GetComponent();
    bool IsFinished() const;
    void Finish();

private:
    Game* game_ = nullptr;

    SelectionMenu menu_;
    std::function<void()> on_finish_;
    std::function<void()> on_submit_;

    bool finished_ = false;
    bool showing_ = false;

    std::vector<Option> options;

    void ShowPending();
    void HandleSelection(int index);
};