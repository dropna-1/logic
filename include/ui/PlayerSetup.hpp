#pragma once

#include <string>
#include <ftxui/component/component.hpp>

struct PlayerInfo {
    std::string name;
    std::string age_str = "0";
    int age = 0;
};

class PlayerSetup {
public:
    PlayerSetup(std::function<void(PlayerInfo p1, PlayerInfo p2)> on_start_);
    ftxui::Component GetComponent();
private:
    PlayerInfo player1_;
    PlayerInfo player2_;

    ftxui::Component p1_name_input_;
    ftxui::Component p1_age_input_;
    ftxui::Component p2_name_input_;
    ftxui::Component p2_age_input_;

    ftxui::Component renderer_;
    std::function<void(PlayerInfo, PlayerInfo)> on_start_;
};