#pragma once

#include <string>
#include <ftxui/component/component.hpp>

class PlayerSetup {
public:
    PlayerSetup();
    ftxui::Component GetComponent();
private:
    std::string name_;
    ftxui::Component name_input_;
    ftxui::Component renderer_;
};