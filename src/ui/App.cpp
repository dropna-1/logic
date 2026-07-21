#include <iostream>
#include "ui/App.hpp"
#include "ui/MainMenu.hpp"
#include "ui/PlayerSetup.hpp"
#include "ui/HeroSelection.hpp"
#include "ui/HelpScreen.hpp"
#include "ui/GameScreen.hpp"
#include "ui/SidekickPlacement.hpp"

App::App() 
: screen_(ftxui::ScreenInteractive::TerminalOutput())
, current_screen_(ScreenType::MainMenu)
{
    game_screen_ = std::make_shared<GameScreen>(
        [this](){SetScreen(ScreenType::MainMenu);}
    );
    
    main_menu_ = std::make_shared<MainMenu>(
    [this](){SetScreen(ScreenType::PlayerSetup);},
    [this](){SetScreen(ScreenType::HelpScreen);},
    [this](){screen_.ExitLoopClosure()();});

    help_screen_ = std::make_shared<HelpScreen>(
        [this](){SetScreen(ScreenType::MainMenu);}
    );

    player_setup_ = std::make_shared<PlayerSetup>(
        [this](PlayerInfo p1, PlayerInfo p2){

            game_ = std::make_unique<Game>();
            game_.get()->setPlayer1(p1.name, p1.age);
            game_.get()->setPlayer2(p2.name, p2.age);
            game_.get()->setupPlayers();

            hero_selection_->SetGame(game_.get());

            SetScreen(ScreenType::HeroSelection);
        }
    );

    hero_selection_ = std::make_shared<HeroSelection>(
        [this](){
            game_.get()->setupGame();
            sidekick_placement_->SetGame(game_.get());
            SetScreen(ScreenType::SidekickPlacement);
        }
    );

    sidekick_placement_ = std::make_shared<SidekickPlacement>(
        [this](){
            game_screen_->SetGame(game_.get());
            SetScreen(ScreenType::GameScreen);
        }
    );

    root_ = ftxui::Container::Tab(
        {
            main_menu_->GetComponent(),
            help_screen_->GetComponent(),
            player_setup_->GetComponent(),
            hero_selection_->GetComponent(),
            sidekick_placement_->GetComponent(),
            game_screen_->GetComponent()
        },
        &current_tab_);
}

void App::SetScreen(ScreenType screen){
    current_screen_ = screen;
    switch (screen)
    {
    case ScreenType::MainMenu:
        current_tab_ = 0;
        break;
    case ScreenType::HelpScreen:
        current_tab_ = 1;
        break;
    case ScreenType::PlayerSetup:
        current_tab_ = 2;
        break;
    case ScreenType::HeroSelection:
        current_tab_ = 3;
        break;
    case ScreenType::SidekickPlacement:
        current_tab_ = 4;
        break; 
    case ScreenType::GameScreen:
        current_tab_ = 5;
        break;   
    default:
        current_tab_ = 0;
        break;
    }
}

void App::Run(){
    screen_.Loop(root_);
}