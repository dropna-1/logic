#include "ui/GameScreen.hpp"
#include "Game/Game.hpp"

#include <ftxui/component/component.hpp>
#include <ftxui/component/event.hpp>
#include <ftxui/dom/elements.hpp>

using namespace ftxui;

GameScreen::GameScreen(std::function<void()> on_exit)
    : on_exit_(std::move(on_exit))
{
    actions_.push_back(" ");
    menu_ = Menu(&actions_, &selected_);

    auto container = Container::Vertical({
        menu_
    });

    component_ = CatchEvent(
        Renderer(container, [&] {
            if (!game_) {
                return text("No Game");
            }
            BuildMenu();

            return vbox({
                info_screen_.Render(
                    game_->getBoard(),
                    *game_->getCurrentPlayer(),
                    *game_->getOtherPlayer()
                ),
                separator(),
                menu_->Render()
            });
        }),

        [this](Event event) {
            if (event == Event::Return) {
                switch (selected_type_.at(selected_)) {
                case SelectedType::Maneuver:
                    // Maneuver
                    break;

                case SelectedType::Combat:
                    // Attack
                    break;

                case SelectedType::Scheme:
                    // Scheme
                    break;

                case SelectedType::EndTurn:
                    game_->changeTurn();
                    break;
                }
                return true;
            }
            return false;
        }
    );
}

void GameScreen::SetGame(Game* game)
{
    game_ = game;
}

Component GameScreen::GetComponent()
{
    return component_;
}

void GameScreen::BuildMenu(){
    actions_.clear();
    if(!game_) return;

    if(game_->canManever()){
        actions_.push_back("Maneuver");
        selected_type_.push_back(SelectedType::Maneuver);
    }
    if(game_->canAttack()){
        actions_.push_back("Combat");
        selected_type_.push_back(SelectedType::Combat);
    }
    if(game_->canPlayScheme()){
        actions_.push_back("Scheme");
        selected_type_.push_back(SelectedType::Scheme);
    }
    actions_.push_back("End Turn");
    selected_type_.push_back(SelectedType::EndTurn);
}