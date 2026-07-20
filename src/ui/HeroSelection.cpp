#include "ui/HeroSelection.hpp"
#include "Game/Game.hpp"

#include <ftxui/component/component.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/component/event.hpp>

using namespace ftxui;

HeroType getHeroType(int index){
    return (index == 0 ? HeroType::Sherlock : HeroType::Dracula);
}

HeroSelection::HeroSelection(std::function<void()> on_finish)
    : on_finish_(std::move(on_finish))
{
    menu_ = Menu(&heroes_, &selected_);

    component_ = CatchEvent(
        Renderer(menu_, [&] {
            return vbox({
                text("Hero Selection --- Choose hero for "+
                (game_ ? game_->getCurrentPlayer()->getName() : ""))
                 | bold | center | color(Color::Cyan),
                separator(),
                menu_->Render() | color(Color::Cyan)
            }) | size(WIDTH, EQUAL, 100) | borderDouble | color(Color::BlueViolet) | center;
        }),
        [this](ftxui::Event event) {
            if (event == Event::Return) {
                SelectHero();
                return true;
            }
            return false;
        }

    );
}

void HeroSelection::SetGame(Game* game)
{
    game_ = game;
}

Component HeroSelection::GetComponent()
{
    return component_;
}

void HeroSelection::SelectHero() {

    if (!game_)
        return;

    if (!first_player_selected_) {
        game_->choiceHero(*game_->getCurrentPlayer(), getHeroType(selected_));
        game_->changeTurn();
        first_player_selected_ = true;
        heroes_.erase(heroes_.begin() + selected_);
        selected_ = 0;
    }
    else {
        game_->choiceHero(*game_->getCurrentPlayer(), getHeroType(0));
        game_->changeTurn();
        if (on_finish_)
            on_finish_();
    }
}