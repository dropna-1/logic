#pragma once
#include <functional>
#include <memory>
#include <string>
#include <vector>

#include <ftxui/component/component.hpp>

class Game;

class HeroSelection {
public:

    HeroSelection(std::function<void()> on_finish);
    void SetGame(Game* game);
    ftxui::Component GetComponent();

private:
    void SelectHero();
    Game* game_ = nullptr;

    std::function<void()> on_finish_;

    std::vector<std::string> heroes_{
        "Sherlock Holmes",
        "Dracula"
    };

    int selected_ = 0;
    bool first_player_selected_ = false;

    ftxui::Component menu_;
    ftxui::Component component_;
};