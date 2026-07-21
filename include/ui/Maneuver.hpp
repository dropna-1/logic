#pragma once
#include <ftxui/component/component.hpp>
#include "Game/Game.hpp"

class Game;
class Character;

class ManeuverHandler {
public:
    explicit ManeuverHandler(Game* game, std::function<void()> on_finish);

    ftxui::Component GetComponent();
    bool IsActive() const {return isActive_;}

private:
    Game* game_ = nullptr;
    std::function<void()> on_finish_;

    bool isActive_ = false;
    Character* selectedCharacter_ = nullptr;

    ftxui::Component characterSelection_;
    ftxui::Component positionSelection_;

    ftxui::Component currentComponent_;

    int selected_ = 0;

    void StartCharacterSelection();
    void StartPositionSelection();
    void CompleteManeuver();
};