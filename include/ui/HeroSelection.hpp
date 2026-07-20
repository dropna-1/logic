#pragma once
#include <functional>
#include <memory>
#include <string>
#include <vector>
#include "Enums/TypeEnums.hpp"

#include <ftxui/component/component.hpp>

class Game;

struct Heroes{
    std::string hero_name_;
    HeroType hero_type_;
};

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

    std::vector<Heroes> type_heroes_{
        {"Sherlock Holmes", HeroType::Sherlock},
        {"Dracula", HeroType::Dracula}
    };

    int selected_ = 0;
    bool first_player_selected_ = false;

    ftxui::Component menu_;
    ftxui::Component component_;
};