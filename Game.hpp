#pragma once
#include <iostream>
#include <vector>
#include "board.hpp"
#include "include/Characters/Hero.hpp"
#include "Factory/HeroFactory.hpp"
#include "Cards/Cards.hpp"
#include "player.hpp"
#include "Pending.hpp"
using namespace std;

struct AttackOption {
    Character* attacker;
    Character* target;
};


struct Option {
    std::string text;
    int id;
};


enum class CombatStage{
    DefenseImmediate,
    AttackImmediate,

    DefenseDuring,
    AttackDuring,

    DealDamage,

    DefenseAfter,
    AttackAfter,

    Discard,
    Finished
};

struct PendingSelection{
    Character* character = nullptr;
    vector<int> cards;
    int destination = -1;
};

struct PendingCombat{
    AttackOption option;

    shared_ptr<Card> attackCard;
    shared_ptr<Card> defenseCard;

    GameContext context;
    CombatStage stage;
    PendingSelection selection;

    PendingCombat(AttackOption option, shared_ptr<Card> attackCard, 
        shared_ptr<Card> defenseCard, GameContext context) : option(option), 
        attackCard(attackCard), defenseCard(defenseCard), context(context),
        stage(CombatStage::DefenseImmediate) {}
};

class Game {

    Board board;

    Player player1;
    Player player2;
    
    shared_ptr<Hero> dracula;
    shared_ptr<Hero> sherlock;

    Player* currentPlayer;
    Player* otherPlayer;

    int actionsRemaining = 2;

    queue<unique_ptr<PendingAction>> pendingActions;
    unique_ptr<PendingCombat> pendingCombat;

public:

    Game();
    void setupGame();
    void startTurn();
    void changeTurn();
    Hero* checkWinner();
    Board& getBoard();
    shared_ptr<Hero> getDracula() const;
    unique_ptr<PendingCombat>& getPendingCombat();
    /*-----------------------------------------------------------------*/
    void setPlayer1(const string& name, const int& age);
    void setPlayer2(const string& name, const int& age);
    Player* getCurrentPlayer();
    Player* getOtherPlayer();
    Player* getFirstPlayer();
    void choiceHero(Player& player, HeroType choice);
    vector<Option> getSidekickPlacement(Character* character);
    const vector<shared_ptr<Card>>& showOtherHand();
    /*-----------------------------------------------------------------*/
    vector<Option> getAvailableMoves(Character* character, const int& spacing);
    vector<Option> getAllSpaces();
    bool canMove(int to) const;
    void move(Character* character, const int& pos);
    int boost(Character* self, vector<int>& cards);
    bool canManever(vector<int> availableMoves) const;
    vector<Option> getFreeSpacesNearby(Character* character);
    /*------------------------------------------------------------------*/
    void requestAction(unique_ptr<PendingAction> action);
    bool hasPendingMove() const;
    PendingAction* currentPendingAction();
    void completePendingMove(const int& position);
    /*------------------------------------------------------------------*/
    bool useAction();
    int getRemainingActions() const;
    void addAction();
    /*------------------------------------------------------------------*/
    vector<AttackOption> getAttackableTargets();
    vector<Card*> getPlayableAttackCard(Character* attacker);
    vector<Card*> getPlayableDefenseCard(Character* defender);
    bool canDefense(vector<Card*> playableDefenseCard) const;
    bool canAttack(vector<Card*> playableAttackCard,
        vector<AttackOption> targets) const;
    vector<Character*> getEnemiesNearby(Character* character);
    /*------------------------------------------------------------------*/
    void playScheme(Character* source, const int& schemeCardIndex);
    vector<Card*> getSchemeCards(Character* character);
    bool canPlayScheme(vector<Card*> playableSchemeCard) const;
    /*------------------------------------------------------------------*/
    int calculateDamage(Card* attack, Card* defense);
    void combat(AttackOption option, const int& attackCardIndex, 
        const int& defenseCardIndex);
    void continueCombat();
};