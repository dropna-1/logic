#include "Pending.hpp"
#include "include/Cards/Deck.hpp"
using namespace std;

MoveAction::MoveAction(Character* Char, MoveMode mode, int value) :
character(Char), mode(mode), range(value) {}


vector<Option> MoveAction::getOption(Game& game){
    if(mode == MoveMode::Range)
        return game.getAvailableMoves(character, range);
    if(mode == MoveMode::AnySpace)
        return game.getAllSpaces();
    if(mode == MoveMode::Zone)
        return game.getSidekickPlacement();

    vector<Option> options;
    for(int neigh : game.getBoard().getSpace(character->getPosition()).neighbors)
        if(game.canMove(neigh))
            options.push_back({"House", neigh});
}


void MoveAction::submit(Game& game, vector<int> choice){
    if(game.canMove(choice.at(0)))
        game.move(character, choice.at(0));
    isFinished = true;
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
    vector<Option> options;
    if(stage == 0){
        for(int id = 0; id < allCharacters.size(); id++)
            options.push_back({allCharacters.at(id)->getname(), id});
        return options;
    }
    return game.getAvailableMoves(selected, 2);
}


void RaveningAction::submit(Game& game, vector<int> choice){
    if(stage == 0){
        selected = allCharacters.at(choice.at(0));
        stage = 1;
    }
    else{
        game.move(selected, choice.at(0));
        isFinished = true;
    }
}


ChooseCardAction::ChooseCardAction(Player* player) : selected(player){}

std::vector<Option> ChooseCardAction::getOption(Game& game){
    vector<Option> options;
    auto p = selected->getHero().get()->getDeck().get()->getHand();
    for(int id = 0; id < p.size(); id++) 
        options.push_back({p.at(id).get()->getName(), id});
    return options;
}

void ChooseCardAction::submit(Game& game, vector<int> choice){}

