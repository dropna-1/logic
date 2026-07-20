#pragma once
#include <memory>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/component/component.hpp>
#include "Game/Game.hpp"

class MainMenu;
class PlayerSetup;
class HeroSelection;

enum class ScreenType{
    MainMenu,
    PlayerSetup,
    HeroSelection,
    GameScreen
};

class App {
public:

    App();
    void Run();
    void SetScreen(ScreenType screen);

private:
    std::unique_ptr<Game> game_;

    ScreenType current_screen_;
    ftxui::ScreenInteractive screen_;
    ftxui::Component root_;
    int current_tab_ = 0;

    std::shared_ptr<MainMenu> main_menu_;
    std::shared_ptr<PlayerSetup> player_setup_;
    std::shared_ptr<HeroSelection> hero_selection_;
};