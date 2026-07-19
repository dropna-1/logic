#include "ui/App.hpp"
#include "ui/MainMenu.hpp"

App::App() 
: screen_(ftxui::ScreenInteractive::TerminalOutput())
, current_screen_(ScreenType::MainMenu) 
{
    main_menu_ = std::make_shared<MainMenu>([this] (){
        SetScreen(ScreenType::PlayerSetup);
        ChangeScreen();
    });

    current_component_ = main_menu_->GetComponent();
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
        break;
    case ScreenType::Exit:
        screen_.ExitLoopClosure()();
    default:
        break;
    }
}

void App::Run(){
    screen_.Loop(current_component_);
}