#include "ui/PlayerSetup.hpp"
#include <ftxui/component/component.hpp>
#include <ftxui/dom/elements.hpp>
#include <string>

using namespace ftxui;

PlayerSetup::PlayerSetup(std::function<void(PlayerInfo, PlayerInfo)> on_start) 
    : on_start_(std::move(on_start))
{
    p1_name_input_ = Input(&player1_.name, "Player 1 name...");
    p1_age_input_  = Input(&player1_.age_str, "Age...");

    p2_name_input_ = Input(&player2_.name, "Player 2 name...");
    p2_age_input_  = Input(&player2_.age_str, "Age...");

    auto start_btn = Button("Next", [this] {
        if(!ValidatePlayers())
            return;

        if(on_start_) on_start_(player1_, player2_);
    });

    auto container = Container::Vertical({
        p1_name_input_, p1_age_input_,
        p2_name_input_, p2_age_input_,
        start_btn
    });

    component_ = Renderer(container, [this, p1n=p1_name_input_, p1a=p1_age_input_,
                                     p2n=p2_name_input_, p2a=p2_age_input_, start=start_btn] {
        auto player1_box = vbox({
            text("Player 1") | bold | center,
            separator(),
            p1n->Render(),
            separator(),
            p1a->Render(),
        }) | borderDouble | color(Color::DarkGoldenrod);

        auto player2_box = vbox({
            text("Player 2") | bold | center,
            separator(),
            p2n->Render(),
            separator(),
            p2a->Render(),
        }) | borderDouble | color(Color::DarkRedBis);

        Elements elements;
        elements.push_back(filler());
        elements.push_back(text("Player Setup") | color(Color::Cyan) | center | bold);
        elements.push_back(separator() | color(Color::Cyan) | bold);
        elements.push_back(player1_box);
        elements.push_back(filler());
        elements.push_back(player2_box);
        elements.push_back(filler());
        if(!error_message_.empty()){
            elements.push_back(text(error_message_) | color(Color::Red) | center);
        }
        elements.push_back(start->Render() | size(ftxui::WIDTH, ftxui::EQUAL, 100) | center);
        elements.push_back(filler());

        return vbox(std::move(elements))
        | borderDouble | color(Color::BlueViolet) 
        | size(WIDTH, EQUAL, 100) | center | bold;
    });
}

bool PlayerSetup::ValidatePlayers() {
    error_message_.clear();

    if (player1_.name.empty()) {
        error_message_ = "Player 1 name is required.";
        return false;
    }
    if (player2_.name.empty()) {
        error_message_ = "Player 2 name is required.";
        return false;
    }
    if (player1_.name == player2_.name) {
        error_message_ = "Players must have different names.";
        return false;
    }
    try {
        player1_.age = std::stoi(player1_.age_str);
        player2_.age = std::stoi(player2_.age_str);
    }
    catch (...) {
        error_message_ = "Age must be a number.";
        return false;
    }
    if (player1_.age <= 0 || player2_.age <= 0) {
        error_message_ = "Age must be greater than 0.";
        return false;
    }
    return true;
}

ftxui::Component PlayerSetup::GetComponent() {
    return component_;
}