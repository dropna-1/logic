#include "ui/SidekickPlacement.hpp"

#include "Game/Game.hpp"
#include "Player/player.hpp"
#include "Characters/Character.hpp"
#include "Characters/SideKick.hpp"
#include "ui/BoardView.hpp"

#include <ftxui/component/component.hpp>
#include <ftxui/component/event.hpp>
#include <ftxui/dom/elements.hpp>

using namespace ftxui;

SidekickPlacement::SidekickPlacement(std::function<void()> on_finish)
    : on_finish_(std::move(on_finish))
{
    menu_ = Menu(&labels_, &selected_);
    component_ = CatchEvent(
        Renderer(menu_, [&] {
            if (!game_)
                return text("No Game");
            BoardView board_view_ ;
            int preview =
            positions_[selected_].id;

            return hbox({

                window(
                    text("Sidekick Placement"),
                    vbox({

                        text("Player : " +
                            game_->getCurrentPlayer()->getName())
                            | center,

                        text("Place : " +
                            current_character_->getname())
                            | center,

                        separator(),

                        menu_->Render()

                    })
                )
                | size(WIDTH, EQUAL, 40),

                separator(),

                board_view_.RenderPlacementPreview(
                    game_->getBoard(),
                    preview
                )

            });

        }),
        [this](Event event){
            if(event == Event::Return){
                PlaceSidekick();
                return true;
            }
            return false;
        }
    );
}

void SidekickPlacement::PlaceSidekick()
{
    int position = positions_[selected_].id;
    current_character_->setPosition(position);

    current_sidekick_++;

    if (current_sidekick_ < sidekicks_.size())
    {
        LoadCurrentSidekick();
        return;
    }
    if(!first_player_finished_)
    {
        first_player_finished_ = true;
        game_->changeTurn();
        current_sidekick_ = 0;
        LoadCurrentSidekick();
        return;
    }
    game_->changeTurn();

    if (on_finish_)
        on_finish_();
}

void SidekickPlacement::LoadCurrentSidekick()
{
    sidekicks_ = game_->getCurrentPlayer()->getHero().get()->getSidekicks();
    current_character_ = sidekicks_.at(current_sidekick_).get();

    positions_ =
        game_->getSidekickPlacement(game_->getCurrentPlayer()->getHero().get());

    labels_.clear();
    for(const auto& option : positions_)
        labels_.push_back(option.text + std::to_string(option.id));

    selected_ = 0;
    menu_ = Menu(&labels_, &selected_);
}

void SidekickPlacement::SetGame(Game* game)
{
    game_ = game;
    current_sidekick_ = 0;
    first_player_finished_ = false;
    LoadCurrentSidekick();
}


ftxui::Component SidekickPlacement::GetComponent(){
    return component_;
}