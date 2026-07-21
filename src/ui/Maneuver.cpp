#include "ui/Maneuver.hpp"
#include <ftxui/component/component.hpp>
#include <ftxui/dom/elements.hpp>
#include "Game/Game.hpp"
#include <string>

using namespace ftxui;

ManeuverHandler::ManeuverHandler(Game* game, std::function<void()> on_finish)
    : game_(game), on_finish_(std::move(on_finish))
{
    StartCharacterSelection();
}

void ManeuverHandler::StartCharacterSelection() {
    if (!game_) return;
    
    std::vector<std::string> characters;
    for(Character* c : game_->getCurrentPlayer()->getAllCharacters())
        characters.push_back(c->getname());

    characterSelection_ = Menu(&characters, &selected_);

    currentComponent_ = Renderer(characterSelection_, [this] {
        return vbox({
            text("Select character to maneuver") | bold,
            characterSelection_->Render()
        });
    });

    isActive_ = true;
}

void ManeuverHandler::StartPositionSelection() {
    selected_ = 0;
    selectedCharacter_ = game_->getCurrentPlayer()->getAllCharacters().at(selected_);
    auto positions = game_->getAvailableMoves(selectedCharacter_, selectedCharacter_->getMovement());

    std::vector<std::string> posList;
    for (auto p : positions) {
        posList.push_back(p.text + std::to_string(p.id));
    }

    positionSelection_ = Menu(&posList, &selected_);

    currentComponent_ = Renderer(positionSelection_, [this] {
        return vbox({
            text("Select destination") | bold,
            positionSelection_->Render()
        });
    });
}

void ManeuverHandler::CompleteManeuver() {
    if (selectedCharacter_ && game_) {
        game_->move(selectedCharacter_, selected_);
    }
    isActive_ = false;
    if (on_finish_) on_finish_();
}

ftxui::Component ManeuverHandler::GetComponent() {
    return currentComponent_;
}