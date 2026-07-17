#pragma once
#include <vector>
#include "Game.hpp"
#include "include/Characters/Character.hpp"

enum class MoveMode
{
    Range,
    Zone,
    AnySpace,
    Neighboor
};

class PendingAction {
protected:
    bool finished = false;
public:
    virtual std::vector<Option> getOption(Game& game) = 0;
    virtual void submit(Game& game, vector<int> choice) = 0;
    bool isFinished() const;
};


class MoveAction : public PendingAction {
private:
    Character* character;
    MoveMode mode;
    int range = 0;
public:
    MoveAction(Character* Char, MoveMode mode, int value);
    std::vector<Option> getOption(Game& game) override;
    void submit(Game& game, vector<int> choice) override;
};


class RaveningAction : public PendingAction {
private:
    std::vector<Character*> allCharacters;
    Character* selected = nullptr;
    int stage = 0;
public:
    RaveningAction(Game& game);
    std::vector<Option> getOption(Game& game) override;
    void submit(Game& game, vector<int> choice) override;
    Character* getSelected() const;
};


class ChooseCardAction : public PendingAction {
private:
    Player* selected = nullptr;
public:
    ChooseCardAction(Player* player);
    std::vector<Option> getOption(Game& game) override;
    void submit(Game& game, vector<int> choice) override;
    Player* getSelected() const;
};