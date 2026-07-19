#pragma once
#include <functional>
#include <ftxui/component/component.hpp>

class MainMenu {
public:
    explicit MainMenu(std::function<void()> on_play);
    ftxui::Component GetComponent();
private:
    std::function<void()> on_play_;
    ftxui::Component component_;
};