#include "ui/PlayerSetup.hpp"
#include <ftxui/component/component.hpp>
#include <ftxui/dom/elements.hpp>

using namespace ftxui;

PlayerSetup::PlayerSetup(){
    name_input_ = Input(name_, "Player name");

    renderer_ = Renderer(name_input_, [&]{
        return vbox({
            text("Player Name"),
            name_input_->Render()
        });
    });
}

ftxui::Component PlayerSetup::GetComponent(){
    return renderer_;
}