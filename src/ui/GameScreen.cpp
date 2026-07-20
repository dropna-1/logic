#include "ui/GameScreen.hpp"
#include "Game/Game.hpp"

#include <ftxui/component/component.hpp>
#include <ftxui/component/event.hpp>
#include <ftxui/dom/elements.hpp>

using namespace ftxui;

GameScreen::GameScreen(std::function<void()> on_exit)
    : on_exit_(std::move(on_exit))
{
    menu_ = Menu(&actions_, &selected_);

    auto container = Container::Vertical({
        menu_
    });

    component_ = CatchEvent(
        Renderer(container, [&] {
            if (!game_) {
                return text("No Game");
            }
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
                switch (selected_) {
                case 0:
                    // Maneuver
                    break;

                case 1:
                    // Attack
                    break;

                case 2:
                    // Scheme
                    break;

                case 3:
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