#include "ui/GameScreen.hpp"
#include "Game/Game.hpp"
#include "ui/Actions/ManeuverAction.hpp"
#include "ui/Actions/CombatAction.hpp"

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

        if (!game_)
            return text("No Game");

        if (!current_action_ && !pending_handler_ && game_->hasPendingAction())
        {
            pending_handler_ =
                std::make_unique<PendingActionHandler>(
                    game_,
                    [this]{pending_handler_.reset();},
                    nullptr
                );
        }

            Element bottom;
            if(current_action_)
                bottom = current_action_->GetComponent()->Render();
            else if(pending_handler_)
                bottom = pending_handler_->GetComponent()->Render();
            else{bottom = menu_->Render();}

            BuildMenu();

            return vbox({
                info_screen_.Render(
                    game_->getBoard(),
                    *game_->getCurrentPlayer(),
                    *game_->getOtherPlayer() ,
                    *game_
                ),
                separator(),
                bottom
            });
        }),

        [this](Event event) {
            if(current_action_)
            {
                current_action_->GetComponent()->OnEvent(event);
                if(current_action_->IsFinished())
                    current_action_.reset();
                return true;
            }
            if(pending_handler_)
            {
                pending_handler_->GetComponent()->OnEvent(event);
                if(pending_handler_->IsFinished())
                    pending_handler_.reset();
                return true;
            }
            if (event == Event::Return) {
                switch (selected_type_.at(selected_)) {
                case SelectedType::Maneuver:
                    current_action_ = std::make_unique<ManeuverAction>(game_);
                    break;

                case SelectedType::Combat:
                    current_action_ = std::make_unique<CombatAction>(game_);
                    break;

                case SelectedType::Scheme:
                    // Scheme
                    break;

                case SelectedType::EndTurn:
                    game_->nextTurn();
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
    selected_type_.clear();
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