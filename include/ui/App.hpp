#pragma once
#include <memory>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/component/component.hpp>

class MainMenu;
class PlayerSetup;

enum class ScreenType{
    MainMenu,
    PlayerSetup,
    HeroSelection,
    GameScreen,
    Exit
};

class App {
public:

    App();
    void Run();
    void SetScreen(ScreenType screen);

private:
    void ChangeScreen();

    ScreenType current_screen_;
    ftxui::ScreenInteractive screen_;
    ftxui::Component current_component_;

    std::shared_ptr<MainMenu> main_menu_;
    std::shared_ptr<PlayerSetup> player_setup_;
};