#pragma once
#include <functional>
#include <string>
#include <memory>
#include <ftxui/component/component.hpp>
#include "ui/InfoScreen.hpp"
#include "ui/Actions/IAction.hpp"


class Game;

enum class SelectedType {
    Maneuver,
    Combat,
    Scheme,
    EndTurn
};

class GameScreen {
public:
    explicit GameScreen(std::function<void()> on_exit);

    void SetGame(Game* game);
    ftxui::Component GetComponent();

private:
    void BuildMenu();

    Game* game_ = nullptr;
    std::function<void()> on_exit_;

    InfoScreen info_screen_;

    std::vector<std::string> actions_;
    std::vector<SelectedType> selected_type_;

    int selected_ = 0;

    ftxui::Component menu_;
    ftxui::Component component_;

    std::unique_ptr<IAction> current_action_;
};