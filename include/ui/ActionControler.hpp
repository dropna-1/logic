#pragma once

#include "ui/SelectionMenu.hpp"
#include "Game/Game.hpp"

class ActionController {
public:
    explicit ActionController(Game* game);

    void StartManeuver();

    ftxui::Component GetComponent();
    bool IsActive() const;

private:
    Game* game_;

    SelectionMenu menu_;

    enum class State {
        None,
        SelectCharacter,
        SelectPosition
    };

    State state_ = State::None;

    Character* selected_character_ = nullptr;
    std::vector<Option> available_positions_;

    void ShowCharacterSelection();
    void ShowPositionSelection();

    void Finish();
};