#pragma once

#include <ftxui/component/component.hpp>

#include <functional>
#include <string>
#include <vector>

class SelectionMenu {
public:
    SelectionMenu();

    void SetItems(const std::vector<std::string>& items);
    void SetTitle(const std::string& items);

    void SetOnAccept(std::function<void(int)> callback);
    void SetOnCancel(std::function<void()> callback);

    int GetSelectedIndex() const;

    ftxui::Component GetComponent();

private:
    std::vector<std::string> items_;
    std::string title_;

    int selected_ = 0;

    std::function<void(int)> onAccept_;
    std::function<void()> onCancel_;

    ftxui::Component menu_;
    ftxui::Component component_;

    void Rebuild();
};