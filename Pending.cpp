#include "Pending.hpp"
#include "include/Cards/Deck.hpp"
using namespace std;

bool PendingAction::isFinished() const {
    return finished;
}

MoveAction::MoveAction(Character* current, Character* other, 
    MoveMode mode, int value) :
currentCharacter(current), otherCharacter(other), 
mode(mode), range(value) {}


vector<Option> MoveAction::getOption(Game& game){
    if(mode == MoveMode::Range){
        spaces = game.getAvailableMoves(currentCharacter, range);
        return spaces;
    }
    if(mode == MoveMode::AnySpace){
        spaces = game.getAllSpaces();
        return spaces;
    }
    if(mode == MoveMode::Zone){
        spaces = game.getSidekickPlacement();
        return spaces;
    }
    spaces = game.getFreeSpacesNearby(otherCharacter);
    return spaces;
}


void MoveAction::submit(Game& game, int choice){
    game.getPendingCombat().get()->selection.destination = spaces.at(choice).id;
    finished = true;
}


RaveningAction::RaveningAction(Game& game){
    if(allCharacters.empty()){
        for(auto i : game.getCurrentPlayer()->getAllCharacters())
            allCharacters.push_back(i);
        for(auto i : game.getCurrentPlayer()->getAllCharacters())
            allCharacters.push_back(i);
    }
}

std::vector<Option> RaveningAction::getOption(Game& game){
    if(stage == 0){
        vector<Option> options;
        for(int id = 0; id < allCharacters.size(); id++)
            options.push_back({allCharacters.at(id)->getname(), id});
        return options;
    }
    spaces = game.getAvailableMoves(selected, 2);
    return spaces;
}


void RaveningAction::submit(Game& game, int choice){
    if(stage == 0){
        selected = allCharacters.at(choice);
        stage = 1;
    }
    else{
        game.getPendingCombat().get()->selection.character = selected;
        game.getPendingCombat().get()->selection.destination = spaces.at(choice).id;
        finished = true;
    }
}


ChooseCardAction::ChooseCardAction(Player* player, int min, int max) : 
selected(player), minCards(min), maxCards(max) {}

std::vector<Option> ChooseCardAction::getOption(Game& game){
    auto p = selected->getHero().get()->getDeck().get()->getHand();
    for(int id = 0; id < p.size(); id++) 
        hand.push_back({p.at(id).get()->getName(), id});
    return hand;
}

void ChooseCardAction::submit(Game& game, int choice=-1){
    if(maxCards == 0){finished = true; return;}
    if(choice != -1)
        cards.push_back(hand.at(choice).id);
    if(maxCards == cards.size()){
        finished = true;
        game.getPendingCombat().get()->selection.cards = cards;
    }
}


std::vector<Option> DraculaAction::getOption(Game& game){
    vector<Option> options;
    neighboors = game.getEnemiesNearby(game.getDracula().get());
    for(auto character : neighboors){
        options.push_back({character->getname(), character->getPosition()});
    }
    return options;
}

void DraculaAction::submit(Game& game, int choice){
    neighboors.at(choice)->takeDamage(1);
}

