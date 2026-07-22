#include "ui/Actions/PendingActionHandler.hpp"

#include "Game/Game.hpp"
#include "Pending/Pending.hpp"
#include <iostream>

#include <ftxui/component/component.hpp>

using namespace ftxui;

PendingActionHandler::PendingActionHandler(Game* game,
    std::function<void()> on_finish,
    std::function<void()> on_submit
)
    : game_(game), on_finish_(std::move(on_finish)), on_submit_(std::move(on_submit)) 
    {ShowPending();}

Component PendingActionHandler::GetComponent()
{
    return menu_.GetComponent();
}

bool PendingActionHandler::IsFinished() const
{
    return finished_;
}

void PendingActionHandler::Finish()
{
    finished_ = true;

    if(on_finish_)
        on_finish_();
}

void PendingActionHandler::ShowPending()
{
    if(!game_ || !game_->hasPendingAction())
    {
        Finish();
        return;
    }

    auto* pending = game_->currentPendingAction();

    auto options = pending->getOption(*game_);
    std::vector<std::string> items;

    for(const auto& option : options)
        items.push_back(option.text + " " + std::to_string(option.id));

    if(items.empty()){
        game_->completePendingAction();
        Finish();
        return;
    }

    menu_.SetTitle("Choose");
    menu_.SetItems(items);

    menu_.SetOnAccept(
        [this, options](int index)
        {
            if(index < 0 ||
               index >= static_cast<int>(options.size()))
            {
                Finish();
                return;
            }
 
            game_->currentPendingAction()->submit(*game_, options[index].id);

            if(game_->currentPendingAction()->isFinished())
                game_->completePendingAction();

            if(on_submit_)
                on_submit_();
            
            if(game_->hasPendingAction())
                ShowPending();
            else
                Finish();
        }
    );

    menu_.SetOnCancel(
        [](){}
    );
}