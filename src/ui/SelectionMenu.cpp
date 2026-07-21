#include "ui/SelectionMenu.hpp"

#include <ftxui/component/component.hpp>
#include <ftxui/component/event.hpp>
#include <ftxui/dom/elements.hpp>

using namespace ftxui;

SelectionMenu::SelectionMenu() {
    Rebuild();
}

void SelectionMenu::SetItems(const std::vector<std::string>& items) {
    items_ = items;
    selected_ = 0;
    Rebuild();
}

void SelectionMenu::SetTitle(const std::string& title){
    title_ = title;
}

void SelectionMenu::SetOnAccept(std::function<void(int)> callback) {
    onAccept_ = std::move(callback);
}

void SelectionMenu::SetOnCancel(std::function<void()> callback) {
    onCancel_ = std::move(callback);
}

int SelectionMenu::GetSelectedIndex() const {
    return selected_;
}

void SelectionMenu::Rebuild() {

    menu_ = Menu(&items_, &selected_);
    component_ = CatchEvent(

        Renderer(menu_, [&] {
            return vbox({
                text(title_) | bold | center,
                separator(),
                menu_->Render()
            });
        }),

        [this](Event event) {

            if(event == Event::Return) {
                if(onAccept_)
                    onAccept_(selected_);
                return true;
            }

            if(event == Event::Escape) {
                if(onCancel_)
                    onCancel_();
                return true;
            }

            return false;
        }
    );
}

Component SelectionMenu::GetComponent() {
    return component_;
}