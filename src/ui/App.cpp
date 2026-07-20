#include <iostream>
#include "ui/App.hpp"
#include "ui/MainMenu.hpp"
#include "ui/PlayerSetup.hpp"

App::App() 
: screen_(ftxui::ScreenInteractive::TerminalOutput())
, current_screen_(ScreenType::MainMenu) 
{
    main_menu_ = std::make_shared<MainMenu>(
    [this](){SetScreen(ScreenType::PlayerSetup);},
    [this](){screen_.ExitLoopClosure()();});

    player_setup_ = std::make_shared<PlayerSetup>(
        [this](PlayerInfo p1, PlayerInfo p2){
            player1_ = &p1;
            player2_ = &p2;

            SetScreen(ScreenType::MainMenu);
        }
    );

    root_ = ftxui::Container::Tab(
        {
            main_menu_->GetComponent(),
            player_setup_->GetComponent()
        },
        &current_tab_);

    ChangeScreen();
}

void App::SetScreen(ScreenType screen){
    current_screen_ = screen;
    switch (screen)
    {
    case ScreenType::MainMenu:
        current_tab_ = 0;
        break;
    case ScreenType::PlayerSetup:
        current_tab_ = 1;
        break;
    default:
        current_tab_ = 0;
        break;
    }
}

void App::ChangeScreen(){
    
}

void App::Run(){
    screen_.Loop(root_);
}