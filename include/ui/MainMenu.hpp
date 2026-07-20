#pragma once
#include <functional>
#include <ftxui/component/component.hpp>

class MainMenu {
public:
    explicit MainMenu(std::function<void()> on_play, std::function<void()> on_help_,
    std::function<void()> on_exit_);
    ftxui::Component GetComponent();
private:
    std::function<void()> on_play_;
    std::function<void()> on_exit_;
    std::function<void()> on_help_;
    ftxui::Component component_;
};