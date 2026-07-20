#pragma once

#include <functional>
#include <ftxui/component/component.hpp>

class HelpScreen {
public:
    HelpScreen(std::function<void()> on_back);
    ftxui::Component GetComponent();

private:
    std::function<void()> on_back_;
    ftxui::Component component_;
};