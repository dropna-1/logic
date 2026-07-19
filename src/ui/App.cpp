#include "ui/App.hpp"
#include "ui/MainMenu.hpp"
#include "ui/PlayerSetup.hpp"

App::App() 
: screen_(ftxui::ScreenInteractive::TerminalOutput())
, current_screen_(ScreenType::MainMenu) 
{
    main_menu_ = std::make_shared<MainMenu>([this](){
        SetScreen(ScreenType::PlayerSetup);
    });

    ChangeScreen();
}

void App::SetScreen(ScreenType screen){
    current_screen_ = screen;
    ChangeScreen();
}

void App::ChangeScreen(){
    switch (current_screen_)
    {
    case ScreenType::MainMenu:
        current_component_ = main_menu_->GetComponent();
        break;
    case ScreenType::PlayerSetup:
        current_component_ =player_setup_->GetComponent();
        break;
    case ScreenType::Exit:
        screen_.ExitLoopClosure()();
        return;
    default:
        current_component_ = main_menu_->GetComponent();
        break;
    }
}

void App::Run(){
    screen_.Loop(current_component_);
}