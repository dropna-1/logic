#pragma once
#include <memory>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/component/component.hpp>

class MainMenu;
class PlayerSetup;
struct PlayerInfo;

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
    PlayerInfo* player1_;
    PlayerInfo* player2_;

    void ChangeScreen();

    ScreenType current_screen_;
    ftxui::ScreenInteractive screen_;
    // ftxui::Component current_component_;
    ftxui::Component root_;
    int current_tab_ = 0;

    std::shared_ptr<MainMenu> main_menu_;
    std::shared_ptr<PlayerSetup> player_setup_;
};