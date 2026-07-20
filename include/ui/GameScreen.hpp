#pragma once
#include <functional>
#include <string>
#include <ftxui/component/component.hpp>
#include <ui/InfoScreen.hpp>

class Game;

class GameScreen {
public:
    GameScreen(std::function<void()> on_exit);

    void SetGame(Game* game);
    ftxui::Component GetComponent();

private:
    Game* game_ = nullptr;
    std::function<void()> on_exit_;

    InfoScreen info_screen_;

    std::vector<std::string> actions_{
        "Maneuver",
        "Attack",
        "Scheme",
        "End Turn"
    };

    int selected_ = 0;

    ftxui::Component menu_;
    ftxui::Component component_;
};