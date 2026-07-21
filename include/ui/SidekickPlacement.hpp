#pragma once

#include <functional>
#include <vector>
#include <string>
#include <memory>

#include <ftxui/component/component.hpp>
#include "Common/Option.hpp"

class Game;
class Character;
class Player;
class SideKick;

class SidekickPlacement {
public:
    explicit SidekickPlacement(std::function<void()> on_finish);

    void SetGame(Game* game);
    ftxui::Component GetComponent();

private:

    void LoadCurrentSidekick();
    void PlaceSidekick();

    Game* game_ = nullptr;

    std::function<void()> on_finish_;

    std::vector<std::shared_ptr<SideKick>> sidekicks_;

    int current_sidekick_ = 0;
    SideKick* current_character_ = nullptr;

    std::vector<Option> positions_;
    std::vector<std::string> labels_;

    int selected_ = 0;
    bool first_player_finished_ = false;

    ftxui::Component menu_;
    ftxui::Component component_;
};